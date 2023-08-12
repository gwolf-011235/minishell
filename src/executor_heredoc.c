/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:05:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/12 15:56:42 by sqiu             ###   ########.fr       */
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
		err = ft_signal_setup(SIG_STD);
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
	pid_t	pid;
	int		status;

	name = NULL;
	err = ft_initiate_heredoc(cmd->index, &name, &fd);
	if (err != SUCCESS)
		return (err);
	g_status = 0;
	pid = fork();
	if (pid < 0)
		return (ERR_FORK);
	else if (pid == 0)
		err = ft_read_heredoc(delim, prompt2, fd, &name);
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) < 0)
		return (ERR_WAIT);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else
		ft_signal_setup(SIG_WSHIT);
	err = ft_heredoc_fate(cmd, &name, fd, curr_delim);
	return (err);
}

t_err	ft_restore_unlink(int fd_stdin, char **name)
{
	//t_err	err;
	(void)fd_stdin;
	//err = ft_signal_setup(SIG_WSHIT);
	//dup2(fd_stdin, 0);
	//close (fd_stdin);
	return (ft_unlink_heredoc(name, ERR_ABORT));
}

/**
 * @brief Read
 *
 * @param delim
 * @param prompt2
 * @param fd
 * @param name
 * @return t_err
 */
t_err	ft_read_heredoc(char *delim, char *prompt2, int fd, char **name)
{
	char	*buf;
	size_t	len;
	int		fd_stdin;
	t_err	err;

	err = ft_signal_setup(SIG_HEREDOC);
	if (err != SUCCESS)
		return (err);
	fd_stdin = dup(0);
	len = ft_strlen(delim);
	while (1)
	{
		buf = readline(prompt2);
		if (g_status == 130)
			return (ft_restore_unlink(fd_stdin, name));
		if (!buf)
			return (ft_print_warning(delim, prompt2));
		if (ft_strncmp(delim, buf, len + 1) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
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

	err = ft_close(fd);
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
