/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:56 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 20:36:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_cleanup2.c
 * @brief Functions to clean up the cmd list
 */

#include "mod_executor.h"

/**
 * @brief Iterate through cmd list and cleanup each cmd.
 *
 * @param cmd	List of cmds.
 */
void	ft_cleanup_cmd_list(t_cmd *cmd, char **paths)
{
	t_cmd	*tmp;

	if (paths)
		ft_free_str_arr(paths);
	while (cmd)
	{
		ft_cleanup_cmd(cmd);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

/**
 * @brief	Clean up and error output if executor encounters ERR_MALLOC
 * 			or ERR_ABORT.
 *
 * @param cmd_head		Head of cmd list.
 * @return t_err		ERR_EXECUTOR
 */
t_err	ft_err_executor(t_cmd *cmd_head, char **paths)
{
	g_status = 1;
	ft_cleanup_cmd_list(cmd_head, paths);
	return (ft_print_error(ERR_EXECUTOR));
}

/**
 * @brief Closes fd_in, fd_out and previous pipe of cmd.
 *
 * @param cmd	Current cmd.
 */
void	ft_close_iopp(t_cmd *cmd)
{
	ft_plug_pipe(&cmd->fd_prev_pipe[0], &cmd->fd_prev_pipe[1]);
	ft_close(&cmd->fd_in);
	ft_close(&cmd->fd_out);
}
