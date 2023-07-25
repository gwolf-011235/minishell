/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 12:56:27 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

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
		err = ft_update_env_var(env_tab, pwd, 3);
		if (err != SUCCESS)
		{
			free(pwd);
			return (err);
		}
		err = ft_update_env_var(env_tab, oldpwd, 6);
		if (err != SUCCESS)
			return (err);
	}
	else
		return (ERR_CHDIR_FAIL);
	return (SUCCESS);
}

t_err	ft_set_home_path(char **path, t_hashtable *env_tab)
{
	t_env_var	*env_home;

	env_home = ft_hashtable_lookup(env_tab, "HOME", 4);
	if (!env_home)
		return (ERR_NOT_FOUND);
	*path = env_home->value;
	return (SUCCESS);
}

t_err	ft_save_cur_pwd(char **oldpwd, t_hashtable *env_tab)
{
	t_env_var	*env_pwd;

	env_pwd = ft_hashtable_lookup(env_tab, "PWD", 3);
	if (env_pwd)
		*oldpwd = ft_strjoin("OLDPWD=", env_pwd->value);
	else
		*oldpwd = ft_strdup("OLDPWD=");
	if (!*oldpwd)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_err	ft_cd(char **argv, t_hashtable *env_tab)
{
	size_t		size;
	char		*oldpwd;
	t_err		err;

	size = 0;
	oldpwd = NULL;
	err = ft_get_array_size(argv, &size);
	if (err != SUCCESS)
		return (err);
	if (size > 2)
		return (ft_cd_error(ERR_ARGCOUNT, oldpwd, NULL));
	err = ft_save_cur_pwd(&oldpwd, env_tab);
	if (err != SUCCESS)
		return (ft_cd_error(err, oldpwd, NULL));
	if (size == 1)
	{
		err = ft_set_home_path(&argv[1], env_tab);
		if (err != SUCCESS)
			return (ft_cd_error(err, oldpwd, NULL));
	}
	err = ft_change_dir(argv[1], env_tab, oldpwd);
	if (err != SUCCESS)
		return (ft_cd_error(err, oldpwd, NULL));
	return (SUCCESS);
}
