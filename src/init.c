/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:51:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 08:11:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a env_table and imports env. If no PWD it creates one
 * Create hashtable env_table with HASHTABLE_SIZE.
 * Call ft_import_env to fill env_table.
 * Check if env was imported, if not set flag no_env to true.
 * Else check if PWD is available, if not set flag no_pwd to true.
 * If either of the flags is true create a env_var PWD.
 * @param data Pointer to data struct.
 * @return t_error SUCCESS if everything went right, else it ft_exit_failures.
 */
t_error	ft_setup_env(t_data *data)
{
	char	*pwd;

	data->env_table = ft_hashtable_create(HASHTABLE_SIZE, ft_hash_fnv1);
	if (!data->env_table)
		ft_exit_failure(data, ERR_MALLOC);
	if (ft_import_env(data) == ERR_EMPTY)
		data->checks.no_env = true;
	else if (ft_hashtable_lookup(data->env_table, "PWD", 3) == NULL)
		data->checks.no_pwd = true;
	if (data->checks.no_env || data->checks.no_pwd)
	{
		pwd = NULL;
		data->err = ft_create_pwd_str(&pwd);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		data->err = ft_hashtable_insert(data->env_table, pwd, 3);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
	}
	return (SUCCESS);
}

/**
 * @brief Import env_vars from global environ
 * Check if environ is not null, else return.
 * Loop trhough the environ array. Environ is NULL-terminated.
 * Strdup the strings and save them in env_table
 * @param data Pointer to data struct
 * @return t_error SUCCESS if environ not empty and mallocs ok.
 */
t_error	ft_import_env(t_data *data)
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
		//TODO: check if valid string?
		keylen = ft_strchr(env_ptr, '=') - env_ptr;
		data->err = ft_hashtable_insert(data->env_table, env_ptr, keylen);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		i++;
	}
	return (SUCCESS);
}
