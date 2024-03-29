/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:11:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/28 10:47:01 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_cleanup.c
 * @brief Functions to clean up executor module after planned/unplanned abort.
 */

#include "mod_executor.h"

/**
 * @brief Cleans cmd after its processing.
 *
 * Close all fds.
 * If present, unlink heredoc.
 * Free all malloced variables.
 * @param cmd 		Cmd to be cleaned.
 */
void	ft_cleanup_cmd(t_cmd *cmd)
{
	if (cmd->heredoc)
		ft_unlink_heredoc(&cmd->heredoc, SUCCESS);
	if (cmd->delims)
		ft_free_str_arr(cmd->delims);
	if (cmd->args)
		ft_free_str_arr(cmd->args);
	if (cmd->outfiles)
		ft_free_str_arr(cmd->outfiles);
	if (cmd->append_switches)
		free(cmd->append_switches);
	if (cmd->hdoc_quoted)
		free(cmd->hdoc_quoted);
}

/**
 * @brief Unlinks the temporary heredoc file created.
 *
 * Returns provided error code.
 * @param name 		Name of heredoc to be unlinked and freed.
 * @param err 		Provided error code.
 * @return t_err 	err
 */
t_err	ft_unlink_heredoc(char **name, t_err err)
{
	unlink(*name);
	free(*name);
	*name = NULL;
	return (err);
}

/**
 * @brief Performs the closing of a file.
 *
 * Returns an error if the closing failed.
 * On success set fd value to -1.
 * @param fd 		Pointer to file descriptor to be closed.
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
t_err	ft_close(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
			return (ERR_CLOSE);
		*fd = -1;
	}
	return (SUCCESS);
}

/**
 * @brief Closes pipe ends (= file descriptors) of the
 * specified cmd.
 *
 * fd_pipe[0] refers to the read end of the pipe.
 * fd_pipe[1] refers to the write end of the pipe.
 * @param cmd		Current cmd.
 * @return t_err	ERR_CLOSE, SUCCESS
 */
t_err	ft_plug_pipe(int *pipe_in, int *pipe_out)
{
	t_err	err;
	t_err	err2;

	err = ft_close(pipe_in);
	err2 = ft_close(pipe_out);
	if (err != SUCCESS)
		return (err);
	return (err2);
}

/**
 * @brief Closes all pipes of cmd list.
 *
 * @param cmd Head of cmd list.
 */
void	ft_plug_all_iopp(t_cmd *cmd)
{
	while (cmd)
	{
		ft_close(&cmd->fd_in);
		ft_close(&cmd->fd_out);
		ft_plug_pipe(&cmd->fd_pipe[0], &cmd->fd_pipe[1]);
		cmd = cmd->next;
	}
}
