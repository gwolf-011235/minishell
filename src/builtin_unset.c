/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:07:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/28 17:51:10 by gwolf            ###   ########.fr       */
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

	i = 1;
	while (argv[i])
	{
		ft_hashtable_delete(env_tab, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (SUCCESS);
}
