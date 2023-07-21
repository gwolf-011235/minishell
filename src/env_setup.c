/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:51:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 16:50:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_setup.c
 * @brief Copy env and generate missing envs.
 */

#include "mod_env.h"

/**
 * @brief Creates a env_table and imports env. If no PWD it creates one.
 *
 * Create hashtable env_table with HASHTABLE_SIZE.
 * Call ft_import_environ to fill env_table.
 * If env was empty set PWD and SHLVL.
 * If PWD is not available set PWD.
 * Increment SHLVL. If not found set it.
 * @param data Pointer to data struct.
 * @return t_err SUCCESS if everything went right, else it ft_exit_failures.
 */
t_err	ft_env_setup(t_hashtable **env_table)
{
	t_err	err;

	*env_table = ft_hashtable_create(HASHTABLE_SIZE, ft_hash_fnv1);
	if (!env_table)
		return (ERR_MALLOC);
	err = ft_import_environ(*env_table);
	if (err == ERR_MALLOC)
		return (ERR_MALLOC);
	if (ft_hashtable_lookup(*env_table, "PWD", 3) == NULL)
	{
		err = ft_insert_env_pwd(*env_table);
		if (err != SUCCESS)
			return (err);
	}
	err = ft_increment_shlvl(*env_table);
	if (err == ERR_NO_SHLVL)
		err = ft_insert_env_shlvl(*env_table);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Import env_vars from global environ.
 *
 * Check if environ is not null, else return.
 * Loop trhough the environ array. Environ is NULL-terminated.
 * Strdup the strings and save them in env_table
 * @param data Pointer to data struct
 * @return t_err SUCCESS if environ not empty and mallocs ok.
 * @todo Check if valid env_str
 */
t_err	ft_import_environ(t_hashtable *env_table)
{
	int		i;
	char	*env_ptr;
	size_t	keylen;
	t_err	err;

	i = 0;
	if (environ[i] == NULL)
		return (ERR_EMPTY);
	while (environ[i] != NULL)
	{
		env_ptr = ft_strdup(environ[i]);
		if (!env_ptr)
			return (ERR_MALLOC);
		keylen = ft_strchr(env_ptr, '=') - env_ptr;
		err = ft_hashtable_insert(env_table, env_ptr, keylen);
		if (err != SUCCESS)
			return (err);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var PWD.
 *
 * If no PWD is present in env_table, this function inserts.
 * @param data
 * @return t_err If SUCCESS it exits
 */
t_err	ft_insert_env_pwd(t_hashtable *env_table)
{
	char	*pwd;
	t_err	err;

	pwd = NULL;
	err = ft_create_env_pwd(&pwd);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_insert(env_table, pwd, 3);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var SHLVL.
 *
 * If no SHLVL is present in env_table, this function inserts.
 * @param data
 * @return t_err If SUCCESS it exits
 */
t_err	ft_insert_env_shlvl(t_hashtable *env_table)
{
	char	*shlvl;
	t_err	err;

	shlvl = NULL;
	err = ft_create_env_shlvl(&shlvl, 1);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_insert(env_table, shlvl, 5);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
