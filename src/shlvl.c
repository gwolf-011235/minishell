/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:45:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file shlvl.c
 * @brief Functions relating to env_var SHLVL
 */

#include "minishell.h"

/**
 * @brief Create an env_var SHLVL starting at 1.
 *
 * If there is no SHLVL present, this function creates one.
 * It always starts at 1.
 * @param shlvl Pointer pointer to change value outside of function.
 * @return t_error SUCCESS or ERR_MALLOC
 */
t_err	ft_create_shlvl_env_str(char **shlvl)
{
	*shlvl = ft_strdup("SHLVL=1");
	if (*shlvl == NULL)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Increments the env_var SHLVL.
 *
 * Search for SHLVL, if not found return error.
 * Extract the number of the found SHLVL and add 1 to it.
 * If the result is bigger than MAX_SHLVL return error.
 * Create a new env_string by converting number to string and join.
 * Update the env_var node by freeing the old string and updating pointers.
 *
 * @param data Big data struct.
 * @return t_error SUCCESS, ERR_NO_SHLVL, ERR_MAX_SHLVL, ERR_MALLOC.
 */
t_err	ft_increment_shlvl(t_data *data)
{
	t_env_var	*shlvl_node;
	int			shlvl_value;
	char		*new_level;
	char		*shlvl_string;

	shlvl_node = ft_hashtable_lookup(data->env_table, "SHLVL", 5);
	if (!shlvl_node)
		return (ERR_NO_SHLVL);
	shlvl_value = ft_atoi(shlvl_node->value) + 1;
	if (shlvl_value > MAX_SHLVL)
		return (ERR_MAX_SHLVL);
	new_level = ft_itoa(shlvl_value);
	if (!new_level)
		return (ERR_MALLOC);
	shlvl_string = ft_strjoin("SHLVL=", new_level);
	free(new_level);
	if (!shlvl_string)
		return (ERR_MALLOC);
	free((void *)shlvl_node->env_string);
	shlvl_node->env_string = shlvl_string;
	shlvl_node->value = shlvl_string + shlvl_node->keylen;
	return (SUCCESS);
}
