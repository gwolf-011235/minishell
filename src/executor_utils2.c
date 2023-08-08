/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:24:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/09 00:22:02 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils2.c
 * @brief Helper functions for executor.
 */

#include "mod_executor.h"

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
 * @brief Create all necessary pipes.
 *
 * Loop through cmd list and create pipe to connect cmds.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Data written to the write end of the pipe is buffered 
 * by the kernel until it is read from the read end of the pipe.
 * Does not create pipe at last cmd.
 * Gives cmds the possibility to access pipe created in
 * predecessor.
 * @param cmd 		List of cmds.
 * @return t_err 	ERR_PIPE, SUCCESS
 */
t_err	ft_create_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->index < cmd->cmd_num - 1)
		{
			if (pipe(cmd->fd_pipe) < 0)
				return (ERR_PIPE);
			cmd->next->fd_prev_pipe[0] = cmd->fd_pipe[0];
			cmd->next->fd_prev_pipe[1] = cmd->fd_pipe[1];
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
