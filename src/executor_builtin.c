/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:47:58 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/07 17:48:31 by sqiu             ###   ########.fr       */
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
 * Return true if found, else false.
 * Compare including '\0' to be sure it is 
 * the cmd and not a str with same head.
 * @param arg 		Cmd str to check.
 * @return true 
 * @return false 
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

t_err	ft_execute_builtin(bool piped, t_cmd *cmd, char **envp, t_data *data)
{
	t_err	err;

	if (piped)
		err = ft_create_child(cmd, envp, data, true);
	else
		ft_choose_builtin(cmd, data);
}
