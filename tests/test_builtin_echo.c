/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:12:15 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 17:07:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char	**g_argv;

void	exec_test_builtin_echo(char *name, char *arg1, char *arg2, char *arg3)
{
	printf("TEST: %s\n", name);
	g_argv[1] = arg1;
	g_argv[2] = arg2;
	g_argv[3] = arg3;
	ft_echo(g_argv);
	printf("**-END-**\n\n");
}

void	test_builtin_echo(void)
{
	test_setup_argv(5);
	g_argv[0] = "echo";
	g_argv[4] = NULL;
	exec_test_builtin_echo("Standard", "Hello", "World", NULL);
	exec_test_builtin_echo("One -n flag", "-n", "No", "newline");
	exec_test_builtin_echo("Two -n flags", "-n", "-n", "I have two flags");
	exec_test_builtin_echo("Three -n flags", "-n", "-n", "-n");
	exec_test_builtin_echo("No args", NULL, NULL, NULL);
	exec_test_builtin_echo("Two -n flags, arg in the middle", "-n", "sneaky", "-n");
	exec_test_builtin_echo("Empty string", "", NULL, NULL);
	exec_test_builtin_echo("Empty string after arg", "First", "", NULL);
	exec_test_builtin_echo("Empty string in the middle", "First", "", "Third");
	test_teardown_argv();
}