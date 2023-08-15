/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 09:30:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_cd.c
 * @brief Implementation of builtin cd.
 */
#include "mod_builtin.h"

/**
 * @brief Builtin cd to change active directory.
 *
 * Check size of input args ft_get_array_size().
 * If more than two args (cd plus path) return error.
 * Save current $PWD for later with ft_save_cur_pwd().
 * If no path arg is given, the NULL-terminator is set to $HOME
 * with ft_set_path_to_home().
 * If $HOME was not found return error.
 * Change directory with ft_change_dir().
 * In case of error call ft_cd_error().
 * @param argv NULL terminated args.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_ARGCOUNT, ERR_MALLOC, ERR_NOT_FOUND
 */
t_err	ft_cd(char **argv, t_hashtable *env_tab)
{
	size_t		size;
	char		*oldpwd;
	t_err		err;

	size = 0;
	oldpwd = NULL;
	ft_get_array_size(argv, &size);
	if (size > 2)
		return (ft_cd_error(ERR_ARGCOUNT, oldpwd, NULL));
	err = ft_save_cur_pwd(&oldpwd, env_tab);
	if (err != SUCCESS)
		return (ft_cd_error(err, oldpwd, NULL));
	if (size == 1)
	{
		err = ft_set_path_to_home(&argv[1], env_tab);
		if (err != SUCCESS)
			return (ft_cd_error(err, oldpwd, NULL));
	}
	err = ft_change_dir(argv[1], env_tab, oldpwd);
	if (err != SUCCESS)
		return (ft_cd_error(err, oldpwd, NULL));
	g_status = 0;
	return (SUCCESS);
}

/**
 * @brief Save the current $PWD for later use.
 *
 * Search environment for $PWD.
 * If found create $OLDPWD env_str.
 * If not found create empty $OLDPWD env_str.
 * @param oldpwd Where to save the env_str.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_save_cur_pwd(char **oldpwd, t_hashtable *env_tab)
{
	t_env_var	*env_pwd;

	env_pwd = ft_hashtable_lookup(env_tab, "PWD", 3);
	if (env_pwd)
		*oldpwd = ft_strjoin("OLDPWD=", env_pwd->value);
	else
		*oldpwd = ft_strdup("OLDPWD");
	if (!*oldpwd)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Look for $HOME and set path to it's value.
 *
 * @param path Pointer which should be changed.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_NOT_FOUND
 */
t_err	ft_set_path_to_home(char **path, t_hashtable *env_tab)
{
	t_env_var	*env_home;

	env_home = ft_hashtable_lookup(env_tab, "HOME", 4);
	if (!env_home)
		return (ERR_NOT_FOUND);
	*path = env_home->value;
	return (SUCCESS);
}

/**
 * @brief Change directory and update environment vars.
 *
 * Change to given path with chdir.
 * Get new pwd env_str with ft_create_env_pwd().
 * Update $PWD in environment with ft_update_env_var().
 * The update $OLDPWD with passed oldpwd.
 * If chdir fails return error.
 * @param path Where to change to.
 * @param env_tab Environment.
 * @param oldpwd Saved pwd env_str to update $OLDPWD.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_EMPTY, ERR_HT_NO_INSERT, ERR_HT_NO_SWAP,
 * ERR_CHDIR_FAIL
 */
t_err	ft_change_dir(char *path, t_hashtable *env_tab, char *oldpwd)
{
	char		*pwd;
	t_err		err;

	if (chdir(path) == 0)
	{
		pwd = NULL;
		err = ft_create_env_pwd(&pwd);
		if (err != SUCCESS)
			return (err);
		err = ft_update_env_var(env_tab, pwd, 3, true);
		if (err != SUCCESS)
		{
			free(pwd);
			return (err);
		}
		err = ft_update_env_var(env_tab, oldpwd, 6, true);
		if (err != SUCCESS)
			return (err);
	}
	else
		return (ERR_CHDIR_FAIL);
	return (SUCCESS);
}
