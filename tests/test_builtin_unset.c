/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:17:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 16:34:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;
extern char			**g_argv;

void	exec_ft_unset(char *name, char *arg1, char *arg2, char *arg3)
{
	printf(BLUE"TEST: %s\n"RESET, name);
	printf("1: %s\n2: %s\n3: %s\n\n", arg1, arg2, arg3);
	g_argv[1] = arg1;
	g_argv[2] = arg2;
	g_argv[3] = arg3;
	printf("\tRUN\n");
	ft_unset(g_argv, g_symtab);
	printf("\n");
	printf("\tPRINT\n");
	ft_hashtable_pretty_print(g_symtab);
	printf("\n");

}

void	test_builtin_unset(void)
{
	printf(YELLOW"**\tTEST BUILTIN UNSET\t**\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_setup_argv(5);
	g_argv[0] = "unset";
	g_argv[4] = NULL;
	ft_hashtable_insert(g_symtab, ft_strdup("uno=this"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("dos=is"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("tr3s=sparta"), 4);
	ft_hashtable_insert(g_symtab, ft_strdup("quatro=!"), 6);
	ft_hashtable_insert(g_symtab, ft_strdup("sneaky=boy"), 6);
	ft_hashtable_pretty_print(g_symtab);
	exec_ft_unset("Unset one var", "uno", NULL, NULL);
	exec_ft_unset("Unset three vars", "dos", "tr3s", "quatro");
	exec_ft_unset("Unset not existing", "sneak", NULL, NULL);
	exec_ft_unset("Unset whole env string", "sneaky=boy", NULL, NULL);
	ft_hashtable_destroy(g_symtab);
	test_teardown_argv();
}
