/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:58:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 19:02:20 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;
extern t_tkn_list	*g_head;

void	exec_expand_tkn_lst(char *testname, char *str)
{
	printf("TEST: %s\n", testname);
	printf("Input: %s\n\n", str);
	ft_lex_input(&g_head, str);
	ft_expand_tkn_lst(&g_head, g_symtab);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	test_expand_list(void)
{
	int			i;
	t_tkn_list	*tmp;

	printf(YELLOW"*******TEST_EXPAND_TKN_LIST*******\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	ft_hashtable_insert(g_symtab, "TEST=USER    SPACEMAN", 4);
	ft_hashtable_insert(g_symtab, "A=at -e", 1);
	ft_hashtable_insert(g_symtab, "LOGFILE=/usr/log/logfile.txt", 7);
	exec_expand_tkn_lst("Simple var expand", "Hello $TEST");
	exec_expand_tkn_lst("Simple heredoc quote removal", "<< 'hello' cat");
	exec_expand_tkn_lst("Simple redirect expand", "echo blub > $NOEXIST");
	exec_expand_tkn_lst("Heredoc, redirect and var", "<< 'never   stop' c$A > $LOGFILE");
}
