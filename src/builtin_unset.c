/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:07:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 17:06:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_unset.c
 * @brief Implementation of builtin unset.
 */
#include "mod_builtin.h"

/**
 * @brief Delete variables out of environment.
 *
 * For every arg try ft_hashtable_delete().
 * Returns always SUCCESS, even if var was not found.
 * @param argv NULL terminated args.
 * @param env_tab Environment.
 */
void	ft_unset(char **argv, t_hashtable *env_tab)
{
	size_t		i;
	t_env_var	*env_var;
	size_t		size;

	i = 1;
	while (argv[i])
	{
		size = 0;
		if (ft_get_env_keylen(argv[i], &size) != SUCCESS)
		{
			i++;
			continue ;
		}
		env_var = ft_hashtable_lookup(env_tab, argv[i], ft_strlen(argv[i]));
		if (env_var)
			ft_hashtable_delete(env_tab, argv[i], ft_strlen(argv[i]));
		i++;
	}
	g_status = 0;
}
