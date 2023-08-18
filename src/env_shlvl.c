/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:45:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 13:55:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_shlvl.c
 * @brief Functions relating to env_var SHLVL
 */

#include "mod_env.h"

/**
 * @brief Create an env_var SHLVL starting at 1.
 *
 * If there is no SHLVL present, this function creates one.
 * if val is 1 just ft_strdup() the str and return.
 * Else convert val to char* with ft_itoa().
 * Create new str with ft_strjoin().
 *
 * @param shlvl Pointer pointer to change value outside of function.
 * @return t_error SUCCESS, ERR_MALLOC
 */
t_err	ft_create_env_shlvl(char **shlvl, int val)
{
	char	*val_str;

	if (val == 1)
	{
		*shlvl = ft_strdup("SHLVL=1");
		if (*shlvl == NULL)
			return (ERR_MALLOC);
		return (SUCCESS);
	}
	val_str = ft_itoa(val);
	if (!val_str)
		return (ERR_MALLOC);
	*shlvl = ft_strjoin("SHLVL=", val_str);
	free(val_str);
	if (!*shlvl)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Increments the env_var SHLVL.
 *
 * Search for $SHLVL, if not found return error.
 * Extract number of found $SHLVL and add 1 to it.
 * If result is higher than MAX_SHLVL return error.
 * Create a new env_string with ft_increment_shlvl().
 * Update $SHLVL with ft_hashtable_swap().
 *
 * @param env_table Environment.
 * @return t_error SUCCESS, ERR_NO_SHLVL, ERR_MALLOC, ERR_EMPTY, ERR_HT_NO_SWAP.
 */
t_err	ft_increment_shlvl(t_hashtable *env_table)
{
	t_env_var	*env_shlvl;
	int			new_val;
	char		*new_str;
	t_err		err;

	env_shlvl = ft_hashtable_lookup(env_table, "SHLVL", 5);
	if (!env_shlvl)
		return (ERR_NO_SHLVL);
	new_val = ft_atoi(env_shlvl->value) + 1;
	if (new_val > MAX_SHLVL)
	{
		printf(MAX, new_val);
		return (ft_hashtable_swap(env_table, "SHLVL=1", 5, true));
	}
	new_str = NULL;
	err = ft_create_env_shlvl(&new_str, new_val);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_swap(env_table, new_str, 5, true);
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
	err = ft_hashtable_insert(env_table, shlvl, 5, true);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
