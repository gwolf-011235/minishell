/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:59:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/15 14:15:02 by gwolf            ###   ########.fr       */
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
 * @return t_err 	ERR_OPEN, ERR_CLOSE, SUCCESS
 */
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new)
{
	int			fd_in;

	*lst = (*lst)->next;
	new->infile = 1;
	if (new->fd_in > -1)
		if (close(new->fd_in) < 0)
			return (ERR_CLOSE);
	fd_in = open((*lst)->content, O_RDONLY);
	if (fd_in == -1)
		return (ERR_OPEN);
	new->fd_in = fd_in;
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
	t_type	type;

	type = (*lst)->type;
	*lst = (*lst)->next;
	if (!new->delims)
		return (SUCCESS);
	if (new->fd_in > -1)
	{
		if (close(new->fd_in) < 0)
			return (ERR_CLOSE);
		new->fd_in = -1;
	}
	new->delims[new->delim_pos] = ft_strdup((*lst)->content);
	if (!new->delims[new->delim_pos])
		return (ERR_MALLOC);
	if (type == QUOTEDOC)
		new->hdoc_quoted[new->delim_pos] = true;
	else
		new->hdoc_quoted[new->delim_pos] = false;
	new->delim_pos++;
	return (SUCCESS);
}

/**
 * @brief Save outfile name and info if append mode is set.
 *
 * Names of outfiles are saved in string array.
 * Append information is saved in bool array.
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @param append	Bool to indicate if append mode is required.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_save_outfile(t_tkn_list **lst, t_cmd *new, bool append)
{
	*lst = (*lst)->next;
	new->outfile = 1;
	new->outfiles[new->out_pos] = ft_strdup((*lst)->content);
	if (!new->outfiles[new->out_pos])
		return (ERR_MALLOC);
	if (append)
		new->append_switches[new->out_pos] = true;
	else
		new->append_switches[new->out_pos] = false;
	new->out_pos++;
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
