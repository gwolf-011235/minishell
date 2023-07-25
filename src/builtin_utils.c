/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 12:54:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_get_array_size(char **array, size_t *size)
{
	if (!array || !size)
		return (ERR_EMPTY);
	while (array[*size])
		(*size)++;
	return (SUCCESS);
}

t_err	ft_update_env_var(t_hashtable *env_tab, char *env_str, size_t keylen)
{
	t_env_var	*env_var;
	t_err		err;

	env_var = ft_hashtable_lookup(env_tab, env_str, keylen);
	if (env_var)
		err = ft_hashtable_swap(env_tab, env_str, keylen);
	else
		err = ft_hashtable_insert(env_tab, env_str, keylen);
	return (err);
}