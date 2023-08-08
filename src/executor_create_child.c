/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_create_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/09 00:40:03 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_create_child.c
 * @brief Functions to create child processes.
 */

#include "mod_executor.h"

/**
 * @brief Distinguishes between the position of the command 
 * to be executed and creates the pertinent child.
 * 
 * @param cmd 		Current cmd to be processed.
 * @param envp 		String array of env.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_create_child(t_cmd *cmd, char **envp, t_data *data, bool builtin)
{
	t_err	err;

	if (cmd->index == 0)
		err = ft_raise_first(cmd, envp, data, builtin);
	else if (cmd->index == cmd->cmd_num - 1)
		err = ft_raise_last(cmd, envp, data, builtin);
	else
		err = ft_raise_middle(cmd, envp, data, builtin);
	return (err);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the child.
 * 
 * The parent does not wait for the child to finish (flag WNOHANG set), it
 * calls its status info immediately. If child has not finished yet,
 * an error code is returned. The parent closes the write end fd of
 * the pipe (fd_pipe[1]).
 * @param cmd 		Current cmd to be processed.
 * @param envp 		String array of env.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_raise_first(t_cmd *cmd, char **envp, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_firstborn(cmd, envp, data, builtin);
	err = ft_close(cmd->fd_pipe[1]);
	if (err != SUCCESS)
		return (err);
	cmd->fd_pipe[1] = -1;
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the child.
 * 
 * The parent waits for the child to finish (no flags set), it
 * retrieves its status info when it's done.
 * @param cmd 	Current cmd to be processed.
 * @param envp 	String array of env.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_raise_last(t_cmd *cmd, char **envp, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_lastborn(cmd, envp, data, builtin);
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the child.
 * 
 * The parent does not wait for the child to finish (flag WNOHANG set), it
 * calls its status info immediately. If child has not finished yet,
 * an error code is returned. The parent closes the write end fd of
 * the pipe (fd_pipe[1]).
 * @param cmd 	Current cmd to be processed.
 * @param envp 	String array of env.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_raise_middle(t_cmd *cmd, char **envp, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_middle_child(cmd, envp, data, builtin);
	err = ft_close(cmd->fd_pipe[1]);
	if (err != SUCCESS)
		return (err);
	cmd->fd_pipe[1] = -1;
	return (SUCCESS);
}
