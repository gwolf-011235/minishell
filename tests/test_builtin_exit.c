/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:35:24 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 15:47:44 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char			**g_argv;
extern t_hashtable	*g_symtab;

void	test_builtin_exit(void)
{
	printf(YELLOW"**\tTEST BUILTIN EXIT\t**\n"RESET);
	printf("\n");
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_setup_argv(5);
	g_argv[0] = "exit";
	g_argv[1] = "+178";
	g_argv[2] = "too much";
	g_argv[4] = NULL;
	ft_exit(g_argv, g_symtab);
	ft_hashtable_destroy(g_symtab);
	test_teardown_argv();
}
