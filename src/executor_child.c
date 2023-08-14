/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:24:49 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/14 14:57:00 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_child.c
 * @brief Behaviour of child processes.
 */

#include "mod_executor.h"

/**
 * @brief First cmd of pipe.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Close all unrequired file descriptors.
 * Assign fds to stdin and stdout.
 * 		If fd_out exists, assign stdout with fd_out, else with fd_pipe[1]
 * 		if fd_in exists, assign stdin with fd_in, else with 0
 * Close assigned fds.
 * Execute cmd.
 * @param cmd 		Current cmd being processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 */
void	ft_firstborn(t_cmd *cmd, t_data *data, bool builtin)
{
	ft_close(&cmd->fd_pipe[0]);
	if (cmd->fd_out >= 0)
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_out);
		else
			ft_replace_fd(0, cmd->fd_out);
		ft_close(&cmd->fd_out);
	}
	else
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_pipe[1]);
		else
			ft_replace_fd(0, cmd->fd_pipe[1]);
		ft_close(&cmd->fd_pipe[1]);
	}
	ft_close(&cmd->fd_in);
	if (builtin)
		ft_choose_builtin(cmd, data);
	else
		if (execve(cmd->args[0], cmd->args, data->envp) < 0)
			printf("\nexecve encountered an error\n");
}

/**
 * @brief Last cmd of pipe.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Close all unrequired file descriptors.
 * The write end of the previous pipe is being closed.
 * Assign fds to stdin and stdout.
 * 		If fd_out exists, assign stdout with fd_out, else with 1.
 * 		if fd_in exists, assign stdin with fd_in, else with fd_prev_pipe[0]
 * Close assigned fds.
 * Execute cmd.
 * @param cmd 		Current cmd being processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 */
void	ft_lastborn(t_cmd *cmd, t_data *data, bool builtin)
{
	ft_close(&cmd->fd_prev_pipe[1]);
	if (cmd->fd_out >= 0)
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_out);
		else
			ft_replace_fd(cmd->fd_prev_pipe[0], cmd->fd_out);
		ft_close(&cmd->fd_out);
	}
	else
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, 1);
		else
			ft_replace_fd(cmd->fd_prev_pipe[0], 1);
	}
	ft_close(&cmd->fd_prev_pipe[0]);
	ft_close(&cmd->fd_in);
	if (builtin)
		ft_choose_builtin(cmd, data);
	else
		if (execve(cmd->args[0], cmd->args, data->envp) < 0)
			printf("\nexecve encountered an error\n");
}

/**
 * @brief Cmd in between the first and last of pipe.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Close all unrequired file descriptors.
 * The write end of the previous pipe is being closed as well as the read
 * end of the current pipe.
 * Assign fds to stdin and stdout.
 * 		If fd_out exists, assign stdout with fd_out, else with fd_pipe[1].
 * 		if fd_in exists, assign stdin with fd_in, else with fd_prev_pipe[0]
 * Close assigned fds.
 * Execute cmd.
 * @param cmd 		Current cmd being processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 */
void	ft_middle_child(t_cmd *cmd, t_data *data, bool builtin)
{
	ft_close(&cmd->fd_prev_pipe[1]);
	ft_close(&cmd->fd_pipe[0]);
	if (cmd->fd_out >= 0)
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_out);
		else
			ft_replace_fd(cmd->fd_prev_pipe[0], cmd->fd_out);
		ft_close(&cmd->fd_out);
	}
	else
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_pipe[1]);
		else
			ft_replace_fd(cmd->fd_prev_pipe[0], cmd->fd_pipe[1]);
	}
	ft_close(&cmd->fd_prev_pipe[0]);
	ft_close(&cmd->fd_pipe[1]);
	ft_close(&cmd->fd_in);
	if (builtin)
		ft_choose_builtin(cmd, data);
	else
		if (execve(cmd->args[0], cmd->args, data->envp) < 0)
			printf("\nexecve encountered an error\n");
}
