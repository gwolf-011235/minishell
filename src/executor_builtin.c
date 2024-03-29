/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:47:58 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 18:22:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_builtin.c
 * @brief Functions to handle execution of built-ins.
 */

#include "mod_executor.h"

/**
 * @brief Verify if given cmd is a builtin.
 *
 * Compare including '\0' to be sure it is
 * the cmd and not a str with same head.
 * @param arg 		Cmd str to check.
 * @return true 	Built-in found.
 * @return false 	Built-in not found.
 */
bool	ft_check_builtin(char *arg)
{
	if (!ft_strncmp(arg, "cd", 3) || !ft_strncmp(arg, "echo", 5)
		|| !ft_strncmp(arg, "env", 4) || !ft_strncmp(arg, "exit", 5)
		|| !ft_strncmp(arg, "export", 7) || !ft_strncmp(arg, "pwd", 4)
		|| !ft_strncmp(arg, "unset", 6))
		return (true);
	return (false);
}

/**
 * @brief Handle built-in execution.
 *
 * Direct built-in call when it is a single cmd.
 * Set file descriptors if fd_in/fd_out are given.
 * Reset file desriptors after built-in execution.
 *
 * Creation of child process when part of a pipe.
 * @param piped 	Bool to differentiate if part of pipe.
 * @param cmd 		Cmd to be processed which is a built-in.
 * @param data 		Data struct containing env.
 * @return t_err 	ERR_FORK, SUCCESS
 */
t_err	ft_execute_builtin(bool piped, t_cmd *cmd, t_data *data)
{
	int		old_stdin;
	int		old_stdout;

	if (piped)
	{
		if (ft_create_child(cmd, data, true) == ERR_FORK)
			return (ERR_FORK);
	}
	else
	{
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup (STDOUT_FILENO);
		ft_set_fd_scmd(cmd);
		ft_choose_builtin(cmd, data);
		ft_reset_fd_scmd(old_stdin, old_stdout);
	}
	return (SUCCESS);
}

/**
 * @brief Set the file descriptors for execution of scmd builtin.
 *
 * @param cmd 		Current cmd.
 */
void	ft_set_fd_scmd(t_cmd *cmd)
{
	if (cmd->fd_out >= 0)
	{
		if (cmd->fd_in >= 0)
			ft_replace_fd(cmd->fd_in, cmd->fd_out);
		else
			ft_replace_fd(0, cmd->fd_out);
		ft_close(&cmd->fd_out);
	}
	ft_close(&cmd->fd_in);
}

/**
 * @brief Reset STDIN_FILENO and STDOUT_FILENO.
 *
 * Stdin and Stdout have been replaced by other fds.
 * They are reset to STDIN_FILENO and STDOUT_FILENO with backup.
 * @return t_err 	SUCCESS
 */
void	ft_reset_fd_scmd(int old_stdin, int old_stdout)
{
	ft_replace_fd(old_stdin, old_stdout);
	ft_close(&old_stdin);
	ft_close(&old_stdout);
}

/**
 * @brief Call suitable built-in.
 *
 * @param cmd 	Cmd containing built-in call and its args.
 * @param data 	Data struct containing env.
 */
void	ft_choose_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd->args, data->env_table, &data->buf);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(data->env_table);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd->args, &data->loop);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd->args, data->env_table);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd(&data->buf);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd->args, data->env_table);
}
