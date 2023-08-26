/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:56 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 14:48:25 by gwolf            ###   ########.fr       */
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
void	ft_cleanup_cmd_list(t_cmd *cmd)
{
	t_err	err;

	while (cmd)
	{
		err = ft_cleanup_cmd(cmd);
/* 		if (err != SUCCESS)
			perror("Closing of fd failed."); */
		cmd = cmd->next;
	}
}

/**
 * @brief	Clean up and error output if executor encounters ERR_MALLOC
 * 			or ERR_ABORT.
 *
 * @param cmd_head		Head of cmd list.
 * @return t_err		ERR_EXECUTOR
 */
t_err	ft_err_executor(t_cmd *cmd_head)
{
	g_status = 1;
	ft_cleanup_cmd_list(cmd_head);
	return (ft_print_error(ERR_EXECUTOR));
}
