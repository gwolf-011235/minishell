/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:59:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/27 00:44:53 by sqiu             ###   ########.fr       */
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
 * @return t_err 	ERR_BAD_FD, SUCCESS
 */
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new)
{
	int			fd_in;
	t_tkn_list	*tmp;

	tmp = *lst;
	tmp = tmp->next;
	new->infile = 1;
	if (new->fd_in > 0)
		close(new->fd_in);
	fd_in = open(tmp->content, O_RDONLY);
/* 	if (fd_in < 3)
		return (ERR_BAD_FD); */
	new->fd_in = fd_in;
	*lst = tmp;
	return (SUCCESS);
}

/**
 * @brief Save token as delimiter string.
 * 
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_save_heredoc(t_tkn_list **lst, t_cmd *new)
{
	t_tkn_list	*tmp;
	char		*buf;
	char		*buf2;

	tmp = *lst;
	tmp = tmp->next;
	if (!new->delim_buf)
		new->delim_buf = ft_strdup(tmp->content);
	else
	{
		buf = ft_strjoin(new->delim_buf, " ");
		free(new->delim_buf);
		buf2 = ft_strjoin(buf, tmp->content);
		if (!buf2)
			return (ERR_MALLOC);
		free(buf);
		new->delim_buf = buf2;
	}
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
	if (new->fd_out)
		close(new->fd_out);
	if (append)
		fd_out = open(tmp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_out < 3)
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
 * @brief Save token as executable and set bool to true.
 * 
 * @param lst 			List of token.
 * @param new 			New cmd to be filled.
 * @param exe_found 	Bool to indicate if executable has been found.
 * @return t_err 		ERR_MALLOC, SUCCESS
 */
t_err	ft_save_exe(t_tkn_list *lst, t_cmd *new, bool *exe_found)
{
	int	len;

	len = ft_strlen(lst->content);
	new->exe = malloc(len + 1);
	if (!new->exe)
		return (ERR_MALLOC);
	ft_strlcpy(new->exe, lst->content, len + 1);
	*exe_found = 1;
	return (SUCCESS);
}

/**
 * @brief 		Save token into arg_buf string.
 * 
 * @param lst 		List of token.
 * @param new 		New cmd to be filled.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_save_arg(t_tkn_list *lst, t_cmd *new)
{
	char	*tmp;
	char	*tmp2;

	if (!new->arg_buf)
		new->arg_buf = ft_strdup(lst->content);
	else
	{
		tmp = ft_strjoin(new->arg_buf, " ");
		free(new->arg_buf);
		tmp2 = ft_strjoin(tmp, lst->content);
		if (!tmp2)
			return (ERR_MALLOC);
		free(tmp);
		new->arg_buf = tmp2;
	}
	return (SUCCESS);
}
