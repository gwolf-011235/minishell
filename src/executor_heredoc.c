/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:05:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 14:02:39 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_heredoc.c
 * @brief Functions to handle heredoc feature.
 */

#include "mod_executor.h"

/**
 * @brief Drive creation of multiple heredocs.
 *
 * @param cmd 		Current cmd being processed.
 * @return t_err 	ERR_MALLOC, ERR_CLOSE, ERR_OPEN, SUCCESS
 */
t_err	ft_handle_heredoc(t_cmd *cmd, t_hashtable *symtab, char *prompt2)
{
	int		i;
	t_err	err;

	while (cmd)
	{
		i = -1;
		while (++i < cmd->delim_pos)
		{
			err = ft_create_heredoc(cmd, i, symtab, prompt2);
			if (err == ERR_MALLOC)
				return (err);
			else if (err == ERR_HEREDOC_OPEN)
				break ;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/**
 * @brief Creates a heredoc file.
 *
 * Stdin (fd = 0) input is written to file until the delimiter
 * is given. Subsequent behaviour handled by ft_heredoc_fate().
 * @param cmd 			Current cmd being processed.
 * @param delim			Delimiter string.
 * @param curr_delim 	Current delimiter index.
 * @param t_err			ERR_MALLOC, ERR_CLOSE, ERR_OPEN, SUCCESS
 */
t_err	ft_create_heredoc(t_cmd *cmd, int curr_delim,
		t_hashtable *symtab, char *prompt2)
{
	t_hdoc	heredoc;
	t_err	err;

	err = ft_init_heredoc(&heredoc, cmd, curr_delim);
	if (err != SUCCESS)
		return (err);
	g_status = 0;
	err = ft_read_heredoc(&heredoc, symtab, prompt2);
	if (err == ERR_ABORT)
	{
		ft_close(&heredoc.fd);
		return (ft_unlink_heredoc(&heredoc.name, ERR_ABORT));
	}
	err = ft_heredoc_fate(cmd, curr_delim, &heredoc);
	return (err);
}

/**
 * @brief Read input for heredoc.
 *
 * Special signal handler set for SIGINT.
 * SIGINT -> g_status set to 130. Causes Heredoc deletion
 * and return of ERR_ABORT.
 * CTRL+D -> Buf is empty. Causes error message and return
 * of ERR_HEREDOC_EOF.
 * Breaks out of loop if delim string is given.
 * @param delim		Delimiter string.
 * @param prompt2	Heredoc prompt string.
 * @param fd		Heredoc file descriptor.
 * @param name		Name of heredoc.
 * @return t_err	ERR_ABORT, ERR_HEREDOC_EOF, SUCCESS
 */
t_err	ft_read_heredoc(t_hdoc *heredoc, t_hashtable *symtab, char *prompt2)
{
	char	*buf;
	t_err	err;

	err = SUCCESS;
	ft_signal_setup(SIGINT, SIG_HEREDOC);
	while (1)
	{
		buf = readline(prompt2);
		if (g_status == 130)
			return (ERR_ABORT);
		if (!buf)
			return (ft_print_warning(ERR_HEREDOC_EOF, heredoc->delim));
		if (ft_strncmp(buf, heredoc->delim, heredoc->delim_len + 1) == 0)
			break ;
		if (heredoc->quoted == false)
			err = ft_expander_heredoc(&buf, symtab);
		if (err != SUCCESS)
			break ;
		ft_putendl_fd(buf, heredoc->fd);
		free(buf);
		buf = NULL;
	}
	free(buf);
	return (err);
}

/**
 * @brief Define the name of the heredoc file to be created.
 *
 * Naming follows a base standard enhanced with the index.
 * @param cmd 		Current cmd being processed.
 * @param name 		Name to be defined.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_name_heredoc(int index, char **name)
{
	char	*index_str;

	index_str = ft_itoa(index);
	*name = ft_strjoin(".tmp_heredoc_v", index_str);
	if (!*name)
	{
		free(index_str);
		return (ERR_MALLOC);
	}
	free(index_str);
	return (SUCCESS);
}

/**
 * @brief Determines usage of heredoc.
 *
 * Heredoc set to fd_in if no infile followed the heredocs (fd_in = -1) and
 * it is the last heredoc among several. Else it is unlinked and its name is
 * freed.
 * @param cmd 			Current cmd being processed.
 * @param name 			Malloced name of heredoc.
 * @param fd 			File descriptor of open heredoc.
 * @param curr_delim 	Current delimiter index.
 * @return t_err 		ERR_CLOSE, ERR_OPEN, SUCCESS
 */
t_err	ft_heredoc_fate(t_cmd *cmd, int curr_delim, t_hdoc *heredoc)
{
	t_err	err;

	err = ft_close(&heredoc->fd);
	if (err != SUCCESS)
		return (err);
	if (cmd->fd_in == -1 && curr_delim == cmd->delim_pos - 1)
	{
		cmd->fd_in = open(heredoc->name, O_RDONLY);
		if (cmd->fd_in == -1)
			return (ft_unlink_heredoc(&heredoc->name, ERR_OPEN));
		cmd->heredoc = heredoc->name;
	}
	else
		ft_unlink_heredoc(&heredoc->name, SUCCESS);
	return (SUCCESS);
}
