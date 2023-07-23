/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:12:15 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 23:21:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char	**g_argv;

void	test_builtin_echo(void)
{
	test_setup_argv(5);
	g_argv[0] = "echo";
	g_argv[1] = "Hallo";
	ft_echo(g_argv);
}