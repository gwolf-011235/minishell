/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:57:58 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 17:19:21 by gwolf            ###   ########.fr       */
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
 * Just calls ft_hashtable_print().
 *
 * @param env_tab Environment.
 * @return t_err SUCCESS.
 */
t_err	ft_env(t_hashtable *env_tab)
{
	ft_hashtable_print(env_tab);
	return (SUCCESS);
}
