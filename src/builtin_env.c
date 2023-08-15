/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:57:58 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 10:12:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_env.c
 * @brief Implementation of builtin env.
 */
#include "mod_builtin.h"

/**
 * @brief Print all environment variables.
 *
 * The strings are not sorted in any way.
 * Check if array at index i has a node.
 * If yes print all nodes found.
 * Check next array index.
 * @param env_tab Environment.
 * @return t_err SUCCESS.
 */
t_err	ft_env(t_hashtable *env_tab)
{
	size_t		i;
	t_env_var	*tmp;

	i = 0;
	while (i < env_tab->size)
	{
		if (env_tab->elements[i] != NULL)
		{
			tmp = env_tab->elements[i];
			while (tmp != NULL)
			{
				if (tmp->has_value)
					printf("%s\n", tmp->env_string);
				tmp = tmp->next;
			}
		}
		i++;
	}
	g_status = 0;
	return (SUCCESS);
}
