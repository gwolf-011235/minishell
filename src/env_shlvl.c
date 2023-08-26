/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:45:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 12:39:17 by gwolf            ###   ########.fr       */
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
	t_err	err;
	char	*val_str;

	val_str = NULL;
	if (val == 1)
	{
		if (ft_err_strdup("SHLVL=1", shlvl,
				"minishell: ft_create_env_shlvl") == ERR_MALLOC)
			return (ERR_MALLOC);
	}
	else if (val == 0)
	{
		if (ft_err_strdup("SHLVL=0", shlvl,
				"minishell: ft_create_env_shlvl") == ERR_MALLOC)
			return (ERR_MALLOC);
	}
	err = ft_err_itoa(val, &val_str, "minishell: ft_create_env_shlvl");
	if (err == ERR_MALLOC)
		return (ERR_MALLOC);
	err = ft_err_strjoin("SHLVL=", val_str, shlvl,
			"minishell: ft_create_env_shlvl");
	free(val_str);
	return (err);
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
 * @return t_error SUCCESS, ERR_MALLOC, ERR_EMPTY, ERR_HT_NO_SWAP.
 */
t_err	ft_increment_shlvl(t_hashtable *env_table)
{
	t_env_var	*env_shlvl;
	int			new_val;
	char		*new_str;
	t_err		err;

	env_shlvl = ft_hashtable_lookup(env_table, "SHLVL", 5);
	if (!env_shlvl)
		return (ERR_EMPTY);
	new_val = ft_atoi(env_shlvl->value) + 1;
	if (new_val < 0)
		new_val = 0;
	if (new_val > MAX_SHLVL)
	{
		ft_print_warning_shlvl(new_val);
		new_val = 1;
	}
	new_str = NULL;
	err = ft_create_env_shlvl(&new_str, new_val);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_swap(env_table, new_str, 5, true);
	if (err == ERR_HT_NO_SWAP)
		free(new_str);
	return (err);
}

/**
 * @brief Creates and inserts the env_var SHLVL.
 *
 * If no SHLVL is present in env_table, this function inserts.
 * @param data
 * @return t_err SUCCESS, ERR_MALLOC, ERR_HT_NO_INSERT, ERR_NOT_FOUND, ERR_EMPTY
 */
t_err	ft_insert_env_shlvl(t_hashtable *env_table)
{
	char	*shlvl;
	t_err	err;

	shlvl = NULL;
	err = ft_create_env_shlvl(&shlvl, 1);
	if (err != SUCCESS)
		return (err);
	errno = 0;
	err = ft_hashtable_insert_export(env_table, shlvl, 5, true);
	if (err == ERR_MALLOC)
		perror("minishell: startup");
	if (err == ERR_MALLOC || err == ERR_HT_NO_INSERT)
		free(shlvl);
	return (err);
}

/**
 * @brief Prints error msg if SHLVL to high.
 *
 * @param new_val New value to be for SHLVL
 */
void	ft_print_warning_shlvl(int new_val)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(new_val, 2);
	ft_putendl_fd(") too high, resetting to 1", 2);
}
