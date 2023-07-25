/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 15:31:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_exit_error(t_err err, char *arg)
{
	if (err == ERR_NONUM)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (err == ERR_EXIT)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (err);
}

t_err	ft_export_error(t_err err, char *arg)
{
	if (err == ERR_INVALID_NAME)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
	}
	else if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: export: malloc() failed", STDERR_FILENO);
	return (err);
}

t_err	ft_pwd_error(t_err err)
{
	if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: pwd: malloc() failed", 2);
	else if (err == ERR_CWD_FAIL)
		ft_putendl_fd("minishell: pwd: getcwd() failed", 2);
	return (err);
}

t_err	ft_cd_error(t_err err, char *oldpwd, char *path)
{
	if (oldpwd)
		free(oldpwd);
	if (err == ERR_ARGCOUNT)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (err == ERR_NOT_FOUND)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: cd: malloc() failed", 2);
	else if (err == ERR_CHDIR_FAIL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	return (err);
}
