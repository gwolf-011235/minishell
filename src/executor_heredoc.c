/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:05:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/15 16:27:56 by sqiu             ###   ########.fr       */
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
t_err	ft_handle_heredoc(t_cmd *cmd, char *prompt2)
{
	int		i;
	t_err	err;

	while (cmd)
	{
		err = ft_signal_setup(SIGINT, SIG_STD);
		if (err != SUCCESS)
			return (err);
		i = -1;
		while (++i < cmd->delim_pos)
		{
			err = ft_create_heredoc(cmd, cmd->delims[i], i, prompt2);
			if (err != SUCCESS)
				return (err);
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
t_err	ft_create_heredoc(t_cmd *cmd, char *delim, int curr_delim,
		char *prompt2)
{
	int		fd;
	char	*name;
	t_err	err;

	name = NULL;
	err = ft_initiate_heredoc(cmd->index, &name, &fd);
	if (err != SUCCESS)
		return (err);
	g_status = 0;
	err = ft_read_heredoc(delim, prompt2, fd, &name);
	if (err != SUCCESS && err != ERR_HEREDOC_EOF)
		return (err);
	err = ft_heredoc_fate(cmd, &name, fd, curr_delim);
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
t_err	ft_read_heredoc(char *delim, char *prompt2, int fd, char **name)
{
	char	*buf;
	size_t	len;

	ft_signal_setup(SIGINT, SIG_HEREDOC);
	len = ft_strlen(delim);
	while (1)
	{
		buf = readline(prompt2);
		if (g_status == 130)
			return (ft_unlink_heredoc(name, ERR_ABORT));
		if (!buf)
			return (ft_print_warning("heredoc", delim));
		if (ft_strncmp(delim, buf, len + 1) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1); 
		free(buf);
		buf = NULL;
	}
	free(buf);
	return (SUCCESS);
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
t_err	ft_heredoc_fate(t_cmd *cmd, char **name, int fd, int curr_delim)
{
	t_err	err;

	err = ft_close(&fd);
	if (err != SUCCESS)
		return (err);
	if (cmd->fd_in == -1 && curr_delim == cmd->delim_pos - 1)
	{
		cmd->fd_in = open(*name, O_RDONLY);
		if (cmd->fd_in < 0)
			return (ft_unlink_heredoc(name, ERR_OPEN));
		cmd->heredoc = *name;
	}
	else
		ft_unlink_heredoc(name, SUCCESS);
	return (SUCCESS);
}
