/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:11:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/13 22:40:48 by sqiu             ###   ########.fr       */
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
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
t_err	ft_cleanup_cmd(t_cmd *cmd)
{
	t_err	err;

	err = ft_close(cmd->fd_in);
	if (err != SUCCESS)
		return (err);
	err = ft_close(cmd->fd_out);
	if (err != SUCCESS)
		return (err);
	err = ft_plug_pipe(cmd);
	if (err != SUCCESS)
		return (err);
	if (cmd->heredoc)
		ft_unlink_heredoc(&cmd->heredoc, err);
	if (cmd->delims)
		ft_free_str_arr(cmd->delims);
	if (cmd->args)
		ft_free_str_arr(cmd->args);
	if (cmd->outfiles)
		ft_remove_outfiles(cmd->outfiles);
	return (SUCCESS);
}

/**
 * @brief Unlink outfiles and free the str array. 
 * 
 * @param outfiles Pointer to string array of outfiles.
 */
void	ft_remove_outfiles(char **outfiles)
{
	int	i;

	i = -1;
	while (outfiles[++i])
		unlink(outfiles[i]);
	ft_free_str_arr(outfiles);
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
 * @param fd 		File descriptor to be closed.
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
t_err	ft_close(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) < 0)
			return (ERR_CLOSE);
		fd = -1;
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
t_err	ft_plug_pipe(t_cmd *cmd)
{
	t_err	err;
	t_err	err2;

	err = ft_close(cmd->fd_pipe[0]);
	err2 = ft_close(cmd->fd_pipe[1]);
	if (err != SUCCESS)
		return (err);
	return (err2);
}
