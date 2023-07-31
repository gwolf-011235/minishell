/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/31 12:39:22 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_executor.h"

t_err	ft_executor(t_cmd *cmd)
{
	ft_init_exec(cmd);
	return (SUCCESS);
}

void	ft_init_exec(t_cmd *cmd)
{
	cmd->cmd_num = 0;
}
