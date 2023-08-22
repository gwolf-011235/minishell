/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:56 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/22 17:28:54 by sqiu             ###   ########.fr       */
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
