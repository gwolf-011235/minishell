/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/08 12:36:48 by sqiu             ###   ########.fr       */
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
 * Get PATH from envp and save it into paths.
 * If no path is found (ERR_NOPATH), try to execute
 * cmd nonetheless in the current directory.
 * @param cmd 		List of cmds.
 * @param envp 		String array with env variables.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_PIPE, SUCCESS
 */
t_err	ft_executor(t_cmd *cmd, char **envp, t_data *data)
{
	t_err	err;
	char	**paths;

	paths = NULL;
	ft_init_exec(cmd);
	err = ft_handle_heredoc(cmd);
	if (err != SUCCESS)
		return (err);
	err = ft_create_pipes(cmd);
	if (err != SUCCESS)
		return (err);
	err = ft_get_path(envp, &paths);
	if (err == ERR_MALLOC)
		return (err);
	if (cmd->next == NULL)
		err = ft_execute_scmd(cmd, envp, paths, data);
	else
		err = ft_execute_pcmds(cmd, envp, paths, data);
	return (err);
}

/**
 * @brief Executes single cmd provided.
 * 
 * @param cmd 		Cmd to be processed.
 * @param envp 		Env string array.
 * @param paths		String array of all system bin paths.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_PIPE, ERR_CLOSE, SUCCESS
 */
t_err	ft_execute_scmd(t_cmd *cmd, char **envp, char **paths, t_data *data)
{
	t_err	err;

	if (ft_check_builtin(cmd->args[0]))
		return (ft_execute_builtin(0, cmd, envp, data));
	err = ft_check_cmd_access(cmd->args, paths);
	err = ft_process_cmd(cmd, err, envp, data);
	if (err != SUCCESS)
		return (err);
	err = ft_wait_for_babies(cmd);
	return (err);
}

/**
 * @brief Executes list of cmds provided.
 * 
 * Create pipes inbetween cmds.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Data written to the write end of the pipe is buffered 
 * by the kernel until it is read from the read end of the pipe.
 * @param cmd 		List of cmds.
 * @param envp 		Env string array.
 * @param paths		String array of all system bin paths.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_PIPE, ERR_CLOSE, SUCCESS
 */
t_err	ft_execute_pcmds(t_cmd *cmd, char **envp, char **paths, t_data *data)
{
	t_err	err;
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd && cmd->index < cmd->cmd_num)
	{
		if (ft_check_builtin(cmd->args[0]))
		{
			err = ft_execute_builtin(1, cmd, envp, data);
			if (err != SUCCESS)
				return (err);
			cmd = cmd->next;
			continue ;
		}
		err = ft_check_cmd_access(cmd->args, paths);
		err = ft_process_cmd(cmd, err, envp, data);
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
 * @param envp 		Env string array.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_MALLOC, ERR_CLOSE, SUCCESS
 */
t_err	ft_process_cmd(t_cmd *cmd, t_err err, char **envp, t_data *data)
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
		err = ft_create_child(cmd, envp, data, false);
	return (err);
}
