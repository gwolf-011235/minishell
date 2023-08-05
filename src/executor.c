/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 18:36:55 by sqiu             ###   ########.fr       */
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
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_executor(t_cmd *cmd, char **envp)
{
	t_err	err;
	char	**paths;

	paths = NULL;
	ft_init_exec(cmd);
	err = ft_get_path(envp, &paths);
	if (err == ERR_MALLOC)
		return (err);
	err = ft_execute_cmds(cmd, envp, paths);
	// clean t_cmd list?
	return (SUCCESS);
}

/**
 * @brief Initialise executor by indexing.
 * 
 * Second run assigns total number of cmds.
 * @param cmd 		List of cmds.
 */
void	ft_init_exec(t_cmd *cmd)
{
	int		count;
	t_cmd	*tmp;

	count = -1;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp->index = count;
		tmp = tmp->next;
	}
	while (cmd)
	{
		cmd->cmd_num = count + 1;
		cmd = cmd->next;
	}
}

/**
 * @brief Executes list of cmds provided.
 * 
 * Create pipes inbetween cmds.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Data written to the write end of the pipe is buffered 
 * by the kernel until it is read from the read end of the pipe.
 * @param cmd 
 * @param envp 
 * @return t_err 
 */
t_err	ft_execute_cmds(t_cmd *cmd, char **envp, char **paths)
{
	int		i;
	t_err	err;

	while (cmd && cmd->index < cmd->cmd_num)
	{
		if (cmd->index < cmd->cmd_num - 1)
			if (pipe(cmd->fd_pipe) < 0)
				return (ERR_PIPE); //no_senor(meta, ERR_PIPE);
		/* if (ft_check_builtin(cmd->args))
			return (ft_execute_builtin(cmd));
		 */
		err = ft_check_cmd_access(cmd->args, paths);
		err = ft_process_cmd(cmd, err, envp);
		if (err != SUCCESS)
			return (err);
		ft_free_str_arr(cmd->args);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/**
 * @brief Decide program behaviour depending on err.
 * 
 * Output error message if command was not found.
 * On success, create child process to execute cmd.
 * @param cmd 		Current cmd being processed.
 * @param err 		Error code of cmd access check.
 * @param envp 		Env string array.
 * @return t_err 	ERR_MALLOC, ERR_CLOSE, SUCCESS
 */
t_err	ft_process_cmd(t_cmd *cmd, t_err err, char **envp)
{
	if (err == ERR_MALLOC)
		return (err);
	else if (err == ERR_UNKNOWN_CMD)
	{
		ft_putstr_fd(cmd->args[0], 2);
		write(2, ": command not found", 19);
		err = ft_close(cmd->fd_pipe[1]);
		if (err != SUCCESS)
			return (err);
	}
	else if (err == SUCCESS)
		ft_create_child(cmd, envp);
	return (SUCCESS);
}
