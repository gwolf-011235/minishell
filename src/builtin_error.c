/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 15:07:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_error.c
 * @brief Error handling functions for builtins.
 */
#include "mod_builtin.h"

/**
 * @brief Handle error of ft_exit().
 *
 * Error if second arg is not numeric.
 * Error if more than two args are given.
 * @param err Error code.
 * @param arg First arg given to ft_exit().
 * @return t_err ERR_NONUM, ERR_EXIT.
 */
t_err	ft_exit_error(t_err err, char *arg)
{
	if (err == ERR_NONUM)
	{
		g_status = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (err == ERR_EXIT)
	{
		g_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	return (err);
}

/**
 * @brief Handle error of ft_export().
 *
 * Error if given name is not valid for env key.
 * Error if malloc failed.
 * @param err Error code.
 * @param arg Current arg given to export.
 * @return t_err ERR_INVALID_NAME, ERR_MALLOC.
 */
t_err	ft_export_error(t_err err, char *arg)
{
	g_status = 1;
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

/**
 * @brief Handle error of ft_pwd().
 *
 * Error if malloc failed.
 * Error if getcwd failed.
 * @param err Error Code.
 * @return t_err ERR_MALLOC, ERR_CWD_FAIL.
 */
t_err	ft_pwd_error(t_err err)
{
	if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: pwd: malloc() failed", 2);
	else if (err == ERR_CWD_FAIL)
		ft_putendl_fd("minishell: pwd: getcwd() failed", 2);
	return (err);
}

/**
 * @brief Handle error of ft_cd().
 *
 * If $PWD has already been saved in oldpwd free it.
 * Error if more than two args are given.
 * Error if $HOME was searched but not found.
 * Error if malloc failed.
 * Error if chdir failed, e.g. given path was not valid.
 * In last case print exact error with perror.
 * @param err Error code
 * @param oldpwd Pointer to saved $PWD.
 * @param path Arg given to chdir.
 * @return t_err ERR_ARGCOUNT, ERR_NOT_FOUND, ERR_MALLOC, ERR_CHDIR_FAIL
 */
t_err	ft_cd_error(t_err err, char *oldpwd)
{
	g_status = 1;
	if (oldpwd)
		free(oldpwd);
	if (err == ERR_ARGCOUNT)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (err == ERR_NO_HOME)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (err == ERR_NO_OLDPWD)
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	else if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: cd: malloc() failed", 2);
	return (err);
}
