/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:07:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 18:44:18 by gwolf            ###   ########.fr       */
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
 * @return t_err SUCCESS.
 */
t_err	ft_unset(char **argv, t_hashtable *env_tab)
{
	size_t		i;
	t_env_var	*env_var;

	i = 1;
	while (argv[i])
	{
		env_var = ft_hashtable_lookup(env_tab, argv[i], ft_strlen(argv[i]));
		if (env_var && env_var->export)
			ft_hashtable_delete(env_tab, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (SUCCESS);
}
