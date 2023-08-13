/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/13 14:34:51 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief Functions to execute the list of cmds.
 */

#include "mod_executor.h"

/**
 * @brief Driver function to execute list of cmds.
 *
 * Index the list of cmds.
 * If heredocs are present in cmd, they are opened
 * and take input from stdin. In case a heredoc is the
 * last infile redirect, its fd is given to the cmd.
 * All necessary pipes are created in advance to ensure
 * definite fd assignment to all pipe ends.
 * Get PATH from envp and save it into paths.
 * If no path is found (ERR_NOPATH), try to execute
 * cmd nonetheless in the current directory.
 * @param cmd 		List of cmds.
 * @param envp 		String array with env variables.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_PIPE, SUCCESS
 */
t_err	ft_executor(t_cmd *cmd, t_data *data)
{
	t_err	err;
	char	**paths;
	bool	empty_path;

	paths = NULL;
	empty_path = false;
	ft_init_exec(cmd);
	err = ft_handle_heredoc(cmd, data->prompt2);
	if (err != SUCCESS)
		return (err);
	err = ft_create_pipes(cmd);
	if (err != SUCCESS)
		return (err);
	err = ft_get_path(data->envp, &paths, &empty_path);
	if (err == ERR_MALLOC)
		return (err);
	if (cmd->args)
	{
		if (cmd->next == NULL)
			err = ft_execute_scmd(cmd, paths, data, empty_path);
		else
			err = ft_execute_pcmds(cmd, paths, data, empty_path);
	}
	return (err);
}

/**
 * @brief Executes single cmd provided.
 *
 * @param cmd 			Cmd to be processed.
 * @param paths			String array of all system bin paths.
 * @param data			Data struct containing the env.
 * @param empty_path	Boolean to determine if PATH contained empty paths.
 * @return t_err 		ERR_MALLOC, ERR_PIPE, ERR_CLOSE, SUCCESS
 */
t_err	ft_execute_scmd(t_cmd *cmd, char **paths, t_data *data, bool empty_path)
{
	t_err	err;

	if (ft_check_builtin(cmd->args[0]))
		return (ft_execute_builtin(0, cmd, data));
	err = ft_check_cmd_access(cmd->args, paths, empty_path);
	err = ft_process_cmd(cmd, err, data);
	if (err != SUCCESS)
		return (err);
	err = ft_wait_for_babies(cmd);
	return (err);
}

/**
 * @brief Executes list of cmds provided.
 *
 * Iterate through the cmd list:
 * 	Check for built-ins.
 * 	If yes, execute built-in and move onto next cmd.
 * 	If no, check for system call by verifying its accessibility.
 * 	On success system call is executed in child process.
 * 	On failure error message is printed.
 * After all cmds/children are launched, the parent waits for
 * each termination.
 * @param cmd 			List of cmds.
 * @param paths			String array of all system bin paths.
 * @param data			Data struct containing the env.
 * @param empty_path	Boolean to determine if PATH contained empty paths.
 * @return t_err 		ERR_MALLOC, ERR_PIPE, ERR_CLOSE, SUCCESS
 */
t_err	ft_execute_pcmds(t_cmd *cmd,
	char **paths, t_data *data, bool empty_path)
{
	t_err	err;
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd && cmd->index < cmd->cmd_num)
	{
		if (ft_check_builtin(cmd->args[0]))
		{
			err = ft_execute_builtin(1, cmd, data);
			if (err != SUCCESS)
				return (err);
			cmd = cmd->next;
			continue ;
		}
		err = ft_check_cmd_access(cmd->args, paths, empty_path);
		err = ft_process_cmd(cmd, err, data);
		if (err != SUCCESS)
			return (err);
		cmd = cmd->next;
	}
	err = ft_wait_for_babies(tmp);
	return (err);
}

/**
 * @brief Decide program behaviour depending on err.
 *
 * Output error message if command was not found.
 * On success, create child process to execute cmd.
 * @param cmd 		Current cmd being processed.
 * @param err 		Error code of cmd access check.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_CLOSE, SUCCESS
 */
t_err	ft_process_cmd(t_cmd *cmd, t_err err, t_data *data)
{
	if (err == ERR_MALLOC)
		return (err);
	else if (err == ERR_UNKNOWN_CMD)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(cmd->args[0], 2);
		write(2, ": command not found\n", 20);
		err = ft_close(cmd->fd_pipe[1]);
	}
	else if (err == SUCCESS)
		err = ft_create_child(cmd, data, false);
	return (err);
}
