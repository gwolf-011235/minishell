/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:51:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 00:15:11 by gwolf            ###   ########.fr       */
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
	err = ft_insert_env_pid(*env_table);
	err = ft_insert_env_prompt(*env_table);
	return (SUCCESS);
}

/**
 * @brief Import env_vars from global environ.
 *
 * Check if environ is not null, else return.
 * Loop through the environ array. Environ is NULL-terminated.
 * Copy the string into environment with ft_copy_envion_str().
 * If ERR_HT_NO_INSERT continue looping. This ensures, that there
 * are no duplicates in environment.
 * If ERR_INVALID_NAME is breaks out of loop (corrupted environ?)
 * @param env_table Environment.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_EMPTY, ERR_INVALID_NAME.
 */
t_err	ft_import_environ(t_hashtable *env_table)
{
	int		i;
	t_err	err;

	i = 0;
	if (environ[i] == NULL)
		return (ERR_EMPTY);
	while (environ[i] != NULL)
	{
		err = ft_copy_environ_str(env_table, environ[i]);
		if (err != SUCCESS && err != ERR_HT_NO_INSERT)
			return (err);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Copies a single string from environ into hashtable.
 *
 * Check if valid env_key with ft_get_env_keylen().
 * If yes generate copy with ft_strdup().
 * If str on pos keylen is an equals sign, the var has a value (standard case).
 * If no equals it has no value, and will not be inserted.
 * If insertion fails free str.
 * @param env_table Environment.
 * @param environ_str Single str from environ.
 * @return t_err SUCCESS, ERR_INVALID_NAME, ERR_MALLOC,
 * ERR_HT_NO_INSERT, ERR_EMPTY
 */
t_err	ft_copy_environ_str(t_hashtable *env_table, char *environ_str)
{
	char	*env_str;
	size_t	keylen;
	t_err	err;

	keylen = 0;
	err = ft_get_env_keylen(environ_str, &keylen);
	if (err == ERR_INVALID_NAME)
		return (err);
	env_str = ft_strdup(environ_str);
	if (!env_str)
		return (ERR_MALLOC);
	if (env_str[keylen] == '=')
		err = ft_hashtable_insert_export(env_table, env_str, keylen, true);
	if (err != SUCCESS && err != ERR_HT_NO_INSERT)
		free(env_str);
	return (err);
}

/**
 * @brief Creates and inserts PS1 and PS2.
 *
 * Gets the prompts from minishell_config.h.
 * @param env_table Environment
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_insert_env_prompt(t_hashtable *env_table)
{
	char	*prompt;
	t_err	err;

	prompt = ft_strdup(PS1);
	if (!prompt)
		return (ERR_MALLOC);
	err = ft_hashtable_insert(env_table, prompt, 3, true);
	if (err != SUCCESS)
		return (err);
	prompt = ft_strdup(PS2);
	if (!prompt)
		return (ERR_MALLOC);
	err = ft_hashtable_insert(env_table, prompt, 3, true);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
