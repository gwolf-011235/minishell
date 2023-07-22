/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:50:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 20:09:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data	g_data;

void	test_builtin_cd(void)
{
	char	*array[2] = {
		"cd",
		NULL
	};

	test_setup_data();
	ft_cd(array, g_data.env_table);
}