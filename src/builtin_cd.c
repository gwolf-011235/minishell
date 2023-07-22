/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 20:10:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_create_env_pwd(char **pwd);

t_err	ft_cd_error(t_err err, char *oldpwd, char *path)
{
	if (oldpwd)
		free(oldpwd);
	if (err == ERR_ARGCOUNT)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (err == ERR_NOT_FOUND)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (err == ERR_MALLOC)
		ft_putstr_fd("minishell: cd: Malloc failed\n", 2);
	else if (err == ERR_CHDIR_FAIL)
	{
		ft_putstr_fd("minishell: cd:", 2);
		perror(path);
	}
	return (err);
}

t_err	ft_set_oldpwd(t_hashtable *env_tab, char *oldpwd)
{
	t_env_var	*env_oldpwd;

	env_oldpwd = ft_hashtable_lookup(env_tab, "OLDPWD", 6);
	if (env_oldpwd)
		ft_hashtable_swap(env_tab, oldpwd, 6);
	else
		ft_hashtable_insert(env_tab, oldpwd, 6);
	free(oldpwd);
	return (SUCCESS);
}

t_err	ft_change_dir(char *path, t_hashtable *env_tab, char *oldpwd)
{
	t_env_var	*env_pwd;
	char		*pwd;
	t_err		err;

	if (chdir(path) == 0)
	{
		pwd = NULL;
		err = ft_create_env_pwd(&pwd);
		if (err != SUCCESS)
			return (ft_cd_error(err, oldpwd, NULL));
		env_pwd = ft_hashtable_lookup(env_tab, "PWD", 3);
		if (env_pwd)
			ft_hashtable_swap(env_tab, pwd, 3);
		else
			ft_hashtable_insert(env_tab, pwd, 3);
		free(pwd);
		ft_set_oldpwd(env_tab, oldpwd);
	}
	else
		ft_cd_error(ERR_CHDIR_FAIL, oldpwd, path);
	return (SUCCESS);
}

t_err	ft_set_home_path(char **path, t_hashtable *env_tab, char *oldpwd)
{
	t_env_var	*env_home;

	env_home = ft_hashtable_lookup(env_tab, "HOME", 4);
	if (!env_home)
		return (ft_cd_error(ERR_NOT_FOUND, oldpwd, NULL));
	*path = env_home->value;
	return (SUCCESS);
}

t_err	ft_cd(char **argv, t_hashtable *env_tab)
{
	size_t		size;
	char		*oldpwd;
	t_env_var	*env_pwd;
	t_err		err;

	size = 0;
	oldpwd = NULL;
	err = ft_get_array_size(argv, &size);
	if (err != SUCCESS)
		return (err);
	if (size > 2)
		return (ft_cd_error(ERR_ARGCOUNT, oldpwd, NULL));
	env_pwd = ft_hashtable_lookup(env_tab, "PWD", 3);
	if (env_pwd)
		oldpwd = ft_strjoin("OLDPWD=", env_pwd->value);
	if (!oldpwd)
		return (ft_cd_error(ERR_MALLOC, oldpwd, NULL));
	if (size == 1)
		ft_set_home_path(&argv[1], env_tab, oldpwd);
	ft_change_dir(argv[1], env_tab, oldpwd);
	return (SUCCESS);
}
