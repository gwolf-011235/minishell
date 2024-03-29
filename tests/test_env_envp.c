/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:17:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 21:07:55wolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;
extern char			**g_envp;

void	test_env_envp_two(void)
{
	size_t		i;

	ft_envp_create(g_symtab, &g_envp);
	printf("This is envp[0]: %p\n", g_envp[0]);
	printf("This is envp[1]: %p\n", g_envp[1]);
	printf("This is envp[2]: %p\n", g_envp[2]);
	i = 0;
	while (g_envp[i])
	{
		printf("This is %lu. symbol: %s\n", i + 1, g_envp[i]);
		i++;
	}
	ft_envp_destroy(&g_envp);

}

void	test_env_envp_empty(void)
{
	ft_envp_create(g_symtab, &g_envp);
	printf("This is envp[0]: %p\n", g_envp[0]);
	ft_envp_destroy(&g_envp);
}

void	exec_envp_create(char *name)
{
	printf("TEST: %s\n", name);
	ft_envp_create(g_symtab, &g_envp);
	test_print_str_array(g_envp);
	ft_envp_destroy(&g_envp);
	printf("\n");
}

void	test_env_envp(void)
{
	g_symtab = ft_hashtable_create(100, ft_hash_fnv1);
	exec_envp_create("Empty environment");
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=This is a value"), 4, true);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST2=Another value"), 5, true);
	exec_envp_create("Two vars");
	ft_hashtable_insert(g_symtab, ft_strdup("NOVAL"), 5, false);
	exec_envp_create("Three vars, one no value");
	ft_hashtable_swap(g_symtab, ft_strdup("TEST"), 4, false);
	exec_envp_create("Three vars, two no value");
	//ft_hashtable_destroy(g_symtab);
}
