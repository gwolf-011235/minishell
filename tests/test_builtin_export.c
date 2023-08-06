/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:38:07 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 21:00:21 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;
extern char			**g_argv;

void	exec_ft_export(char *name, char *arg1, char *arg2, char *arg3)
{
	printf(BLUE"TEST: %s\n"RESET, name);
	printf("1: %s\n2: %s\n3: %s\n\n", arg1, arg2, arg3);
	g_argv[1] = arg1;
	g_argv[2] = arg2;
	g_argv[3] = arg3;
	printf("\tRUN\n");
	ft_export(g_argv, g_symtab);
	printf("\n");
	printf("\tPRINT\n");
	test_hashtable_pretty_print(g_symtab);
	printf("\n");
}

void	test_builtin_export(void)
{
	printf(YELLOW"**\tTEST BUILTIN EXPORT\t**\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_setup_argv(5);
	g_argv[0] = "export";
	g_argv[4] = NULL;
	exec_ft_export("Simple insert", "test=hello", NULL, NULL);
	exec_ft_export("Triple insert", "uno=this", "dos=is", "tres=sparta");
	exec_ft_export("Invalid name", "1=error", NULL, NULL);
	exec_ft_export("Swap existing", "test=new", NULL, NULL);
	exec_ft_export("Good, bad, ugly", "good=boy", "{bad=boy", "_ugly=boy");
	exec_ft_export("Insert just var name", "lonely", NULL, NULL);
	exec_ft_export("No args", NULL, NULL, NULL);
	ft_hashtable_destroy(g_symtab);
	test_teardown_argv();
}

