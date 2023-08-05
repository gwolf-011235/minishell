/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:11:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 16:17:06 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_executor.h"

/* This function terminates the program and displays an error message 
according to the point in the program where the error happened. */

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

/* This function closes all open file descriptors, frees allocated memory
space in the heap and unlinks any files at the current point. It then
gives out an error message and terminates the program. */

void	abort_mission(t_meta *meta, char *s)
{
	if (meta->here_doc)
		unlink(".tmp_heredoc");
	ft_close(meta->fd_in);
	ft_close(meta->fd_out);
	free(meta->cmds);
	terminate(s);
}

/* This function frees the cmd_paths and calls 'abort_mission' upon an
error. */

void	no_senor(t_meta *meta, char *s)
{
	int	i;

	i = -1;
	while (meta->cmd_paths[++i])
		free(meta->cmd_paths[i]);
	free(meta->cmd_paths);
	abort_mission(meta, s);
}

/* This function frees the arguments in the current command and 
calls 'no senor' upon an error. */

void	mamma_mia(t_meta *meta, char *s)
{
	int	i;

	i = -1;
	while (meta->cmds[meta->i].arg[++i])
		free(meta->cmds[meta->i].arg[i]);
	free(meta->cmds[meta->i].arg);
	no_senor(meta, s);
}

/* This function closes remaining file descriptors and frees allocated 
memory space. */

void	cleanup(t_meta *meta)
{
	int	i;

	if (meta->here_doc)
		unlink(".tmp_heredoc");
	ft_close(meta->fd_in);
	ft_close(meta->fd_out);
	i = -1;
	while (meta->cmd_paths[++i])
		free(meta->cmd_paths[i]);
	free(meta->cmd_paths);
	free(meta->cmds);
}

/**
 * @brief Unlinks the temporary heredoc file created.
 * 
 * Returns provided error code.
 * @param name 		Name of heredoc to be unlinked.
 * @param err 		Provided error code.
 * @return t_err 	err
 */
t_err	ft_unlink_heredoc(char *name, t_err err)
{
	unlink(name);
	free(name);
	return (err);
}

/**
 * @brief Performs the closing of a file.
 * 
 * Returns an error if the closing failed. * 
 * @param fd 		File descriptor to be closed.
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
t_err	ft_close(int fd)
{
	if (fd >= 0)
		if (close(fd) < 0)
			return (ERR_CLOSE);
	return (SUCCESS);
}

/* This function closes all pipes which have been created. 
It executes the closing for all pipes created in previous
and including the current loop except if the the current
loop is the last loop. */

void	pipinator(t_meta *meta)
{
	int	j;

	j = -1;
	while (++j <= meta->i)
	{
		if (j < meta->cmd_num - 1)
			plug_pipes(meta, j);
	}
}

/* This function closes the pipe ends (= file descriptors) of the
specified pipe. */

void	plug_pipes(t_meta *meta, int i)
{
	ft_close(meta->cmds[i].fd[0]);
	ft_close(meta->cmds[i].fd[1]);
}