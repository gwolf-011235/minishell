/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:17:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 13:25:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;
extern char			**g_argv;

void	test_builtin_unset(void)
{
	printf(YELLOW"**\tTEST BUILTIN UNSET\t**\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_setup_argv(4);
	g_argv[0] = "unset";
	g_argv[1] = "uno";
	g_argv[2] = NULL;
	ft_hashtable_insert(g_symtab, ft_strdup("uno=this"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("dos=is"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("tr3s=sparta"), 4);
	ft_hashtable_print(g_symtab);
	ft_unset(g_argv, g_symtab);
	ft_hashtable_print(g_symtab);

}