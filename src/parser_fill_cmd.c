/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:59:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/04 13:10:36 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_fill_cmd.c
 * @brief Functions to fill the cmd struct.
 */

#include "mod_parser.h"

/**
 * @brief Open file and save fd as fd_in.
 * 
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @return t_err 	ERR_BAD_FD, ERR_CLOSE, SUCCESS
 */
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new)
{
	int			fd_in;
	t_tkn_list	*tmp;

	tmp = *lst;
	tmp = tmp->next;
	new->infile = 1;
	if (new->fd_in > -1)
		if (close(new->fd_in) < 0)
			return (ERR_CLOSE);
	fd_in = open(tmp->content, O_RDONLY);
/* 	if (fd_in == -1)
		return (ERR_BAD_FD); */
	new->fd_in = fd_in;
	*lst = tmp;
	return (SUCCESS);
}

/**
 * @brief Save token as delimiter string.
 * 
 * If no memory space is allocated for delimiters, return.
 * In case an infile has been opened before, close the fd.
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_save_heredoc(t_tkn_list **lst, t_cmd *new)
{
	t_tkn_list	*tmp;

	tmp = *lst;
	tmp = tmp->next;
	if (!new->delims)
		return (SUCCESS);
	if (new->fd_in > -1)
	{
		if (close(new->fd_in) < 0)
			return (ERR_CLOSE);
		new->fd_in = -1;
	}
	new->delims[new->delim_pos] = ft_strdup(tmp->content);
	if (!new->delims[new->delim_pos])
		return (ERR_MALLOC);
	new->delim_pos++;
	*lst = tmp;
	return (SUCCESS);
}

/**
 * @brief Open file and save fd as fd_out.
 * 
 * If append bool is true, open file in append mode.
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @param append	Bool to indicate if append mode is required.
 * @return t_err 	ERR_BAD_FD, SUCCESS
 */
t_err	ft_save_outfile(t_tkn_list **lst, t_cmd *new, bool append)
{
	int			fd_out;
	t_tkn_list	*tmp;

	tmp = *lst;
	tmp = tmp->next;
	new->outfile = 1;
	if (new->fd_out > -1)
		if (close(new->fd_out) < 0)
			return (ERR_CLOSE);
	if (append)
		fd_out = open(tmp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		return (ERR_BAD_FD);
	new->fd_out = fd_out;
	if (append)
		new->append = 1;
	else
		new->append = 0;
	*lst = tmp;
	return (SUCCESS);
}

/**
 * @brief 		Save token into args string array.
 * 
 * After successful save, increase arg position to
 * allow next arg to be saved in the right position.
 * If there is no args string array, just return.
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_save_arg(t_tkn_list *lst, t_cmd *new)
{
	if (!new->args)
		return (SUCCESS);
	new->args[new->arg_pos] = ft_strdup(lst->content);
	if (!new->args[new->arg_pos])
		return (ERR_MALLOC);
	new->arg_pos++;
	return (SUCCESS);
}
