/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:50:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 14:36:29 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data	g_data;
extern char		**g_argv;

void	execute_cd_test(char *name, char *path)
{
	char	*pwd;

	printf("TEST: %s\n", name);
	pwd = NULL;
	ft_create_pwd_value(&g_data.buf);
	printf("Current pwd: %s\n", g_data.buf);
	g_argv[1] = path;
	ft_cd(g_argv, g_data.env_table, &g_data.buf);
	ft_create_pwd_value(&g_data.buf);
	printf("After change: %s\n\n", g_data.buf);
	free(pwd);
}

void	test_builtin_cd(void)
{
	printf(YELLOW"**\tTEST BUILTIN CD\t**\n\n"RESET);
	test_setup_data();
	test_setup_argv(4);
	g_argv[0] = "cd";
	g_argv[2] = NULL;
	execute_cd_test("Existing path /usr", "/usr");
	execute_cd_test("No arg = $HOME", NULL);
	execute_cd_test("Double dot", "..");
	execute_cd_test("Single dot", ".");
	execute_cd_test("Not existing dir", "/garbage");
	ft_hashtable_delete(g_data.env_table, "HOME", 4);
	execute_cd_test("HOME not set", NULL);
	g_argv[2] = "garbage";
	g_argv[3] = NULL;
	execute_cd_test("Too many args", "/usr");
	test_teardown_data();
	test_teardown_argv();
}
