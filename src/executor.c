/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/04 10:50:26 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief Functions to execute the list of cmds.
 */

#include "mod_executor.h"

/**
 * @brief 
 * 
 * @param cmd 
 * @param envp 
 * @return t_err 
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
	return (SUCCESS);
}

/**
 * @brief 
 * 
 * @param cmd 
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
	int	i;

	while (cmd && cmd->index < cmd->cmd_num)
	{
		if (cmd->index < cmd->cmd_num - 1)
			if (pipe(cmd->fd_pipe) < 0)
				return (ERR_PIPE); //no_senor(meta, ERR_PIPE);
		if (ft_check_builtin(cmd->args))
			return (ft_execute_builtin(cmd));
		cmd->args[0] = ft_prefix_path(cmd->args[0], paths);
		if (!cmd->args[0])
			return (ERR_UNKNOWN_CMD);
		ft_create_child(cmd, envp);
		i = -1;
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
