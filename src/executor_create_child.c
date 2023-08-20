/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_create_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/19 20:44:13 by gwolf            ###   ########.fr       */
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
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, SUCCESS
 */
t_err	ft_create_child(t_cmd *cmd, t_data *data, bool builtin)
{
	t_err	err;

	if (cmd->index == 0)
		err = ft_raise_first(cmd, data, builtin);
	else if (cmd->index == cmd->cmd_num - 1)
		err = ft_raise_last(cmd, data, builtin);
	else
		err = ft_raise_middle(cmd, data, builtin);
	return (err);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the first cmd of the pipe.
 *
 * The parent closes the write end fd of the pipe (fd_pipe[1]).
 * @param cmd 		Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, ERR_SIGNAL SUCCESS
 */
t_err	ft_raise_first(t_cmd *cmd, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(&cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_firstborn(cmd, data, builtin);
	else
	{
		ft_signal_setup(SIGINT, SIG_IGNORE);
		err = ft_close(&cmd->fd_pipe[1]);
		err = ft_close(&cmd->fd_out);
		if (err != SUCCESS)
			return (err);

	}
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by the last cmd of the pipe.
 *
 * @param cmd 		Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, ERR_SIGNAL, SUCCESS
 */
t_err	ft_raise_last(t_cmd *cmd, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(&cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_lastborn(cmd, data, builtin);
	else
		ft_signal_setup(SIGINT, SIG_IGNORE);
	return (SUCCESS);
}

/**
 * @brief Creates a child by forking and calls the pertinent
 * function which is to be executed by a cmd between the first
 * and last cmd of the pipe.
 *
 * The parent closes the write end fd of the pipe (fd_pipe[1]).
 * @param cmd 	Current cmd to be processed.
 * @param data		Data struct containing the env.
 * @param builtin	Bool indicating if cmd is a builtin.
 * @return t_err	ERR_CLOSE, ERR_FORK, ERR_SIGNAL, SUCCESS
 */
t_err	ft_raise_middle(t_cmd *cmd, t_data *data, bool builtin)
{
	t_err	err;

	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		err = ft_close(&cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_middle_child(cmd, data, builtin);
	else
	{
		ft_signal_setup(SIGINT, SIG_IGNORE);
		err = ft_close(&cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
	}
	return (SUCCESS);
}
