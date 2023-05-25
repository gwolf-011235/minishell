/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:51:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 14:49:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 * @brief Copy env and generate missing envs.
 */

#include "minishell.h"

/**
 * @brief Creates a env_table and imports env. If no PWD it creates one.
 *
 * Create hashtable env_table with HASHTABLE_SIZE.
 * Call ft_env_import to fill env_table.
 * If env was empty set PWD and SHLVL.
 * If PWD is not available set PWD.
 * Increment SHLVL. If not found set it.
 * @param data Pointer to data struct.
 * @return t_error SUCCESS if everything went right, else it ft_exit_failures.
 */
t_error	ft_env_setup(t_data *data)
{
	data->env_table = ft_hashtable_create(HASHTABLE_SIZE, ft_hash_fnv1);
	if (!data->env_table)
		ft_exit_failure(data, ERR_MALLOC);
	if (ft_env_import(data) == ERR_EMPTY)
	{
		ft_env_insert_pwd(data);
		ft_env_insert_shlvl(data);
	}
	if (ft_hashtable_lookup(data->env_table, "PWD", 3) == NULL)
		ft_env_insert_pwd(data);
	if (ft_increment_shlvl(data) == ERR_NO_SHLVL)
		ft_env_insert_shlvl(data);
	return (SUCCESS);
}

/**
 * @brief Import env_vars from global environ.
 *
 * Check if environ is not null, else return.
 * Loop trhough the environ array. Environ is NULL-terminated.
 * Strdup the strings and save them in env_table
 * @param data Pointer to data struct
 * @return t_error SUCCESS if environ not empty and mallocs ok.
 * @todo Check if valid env_str
 */
t_error	ft_env_import(t_data *data)
{
	int		i;
	char	*env_ptr;
	size_t	keylen;

	i = 0;
	if (environ[i] == NULL)
		return (ERR_EMPTY);
	while (environ[i] != NULL)
	{
		env_ptr = ft_strdup(environ[i]);
		if (!env_ptr)
			ft_exit_failure(data, ERR_MALLOC);
		keylen = ft_strchr(env_ptr, '=') - env_ptr;
		data->err = ft_hashtable_insert(data->env_table, env_ptr, keylen);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var PWD.
 *
 * If no PWD is present in env_table, this function inserts.
 * @param data
 * @return t_error If SUCCESS it exits
 */
t_error	ft_env_insert_pwd(t_data *data)
{
	char	*pwd;

	pwd = NULL;
	data->err = ft_create_pwd_env_str(&pwd);
	if (data->err != SUCCESS)
		ft_exit_failure(data, data->err);
	data->err = ft_hashtable_insert(data->env_table, pwd, 3);
	if (data->err != SUCCESS)
		ft_exit_failure(data, data->err);
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var SHLVL.
 *
 * If no SHLVL is present in env_table, this function inserts.
 * @param data
 * @return t_error If SUCCESS it exits
 */
t_error	ft_env_insert_shlvl(t_data *data)
{
	char	*shlvl;

	shlvl = NULL;
	data->err = ft_create_shlvl_env_str(&shlvl);
	if (data->err != SUCCESS)
		ft_exit_failure(data, data->err);
	data->err = ft_hashtable_insert(data->env_table, shlvl, 5);
	if (data->err != SUCCESS)
		ft_exit_failure(data, data->err);
	return (SUCCESS);
}
