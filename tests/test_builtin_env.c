/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:03:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 14:04:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data	g_data;

void	test_builtin_env(void)
{
	test_setup_data();
	ft_env(&g_data.env_table);
	test_teardown_data();
}
