/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:58:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 19:59:18 by gwolf            ###   ########.fr       */
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
	ft_hashtable_insert(g_symtab, "TEST=USER    SPACEMAN", 4, true);
	ft_hashtable_insert(g_symtab, "A=at -e", 1, true);
	ft_hashtable_insert(g_symtab, "LOGFILE=/usr/log/logfile.txt", 7, true);
	ft_hashtable_insert(g_symtab, "HOME=/usr/home", 4, true);
	//HEREDOC
	exec_expand_tkn_lst("Heredoc quote removal", "<< 'hello' cat");
	//REDIRECT
	exec_expand_tkn_lst("Redirect expand", "echo blub > $TEST");
	exec_expand_tkn_lst("Redirect Ambiguous", "echo blub > $NOEXIST");
	exec_expand_tkn_lst("Redirect Empty string", "echo blub > \"$NOEXIST\"");
	exec_expand_tkn_lst("Redirect tilde start", "echo blub > ~/dir/log");
	exec_expand_tkn_lst("Redirect tilde mid", "echo blub > no/expand/pls/~/dir/log");
	//ASSIGN
	exec_expand_tkn_lst("Assign expand", "VAR=$TEST");
	exec_expand_tkn_lst("Assign no exist", "VAR=$NOEXIST");
	exec_expand_tkn_lst("Assign in heredoc", "<< VAR=$TEST");
	exec_expand_tkn_lst("Arg, Assign, Assign", "export VAR=$TEST _VAR2=String");
	exec_expand_tkn_lst("Assign, Arg, Assign", "VAR=$TEST export _VAR2=String");
	exec_expand_tkn_lst("Assign with tilde", "VAR=~/test");
	exec_expand_tkn_lst("Assign with tilde mid", "VAR=no/expand/~/test");
	//VAR
	exec_expand_tkn_lst("Var expand", "Hello $TEST");
	exec_expand_tkn_lst("Var no exist", "$NOEXIST");
	exec_expand_tkn_lst("Var multiple expand", "Hello$TEST\"$NOEXIST\"yada\"   \"sisi");
	exec_expand_tkn_lst("Var Expand then no expand", "\"$TEST\"$1");
	exec_expand_tkn_lst("Var expand, then empty then var", "\"$TEST\"$NOEXIST$TEST");
	exec_expand_tkn_lst("Var with tilde", "Hello ~");
	//Multiple
	exec_expand_tkn_lst("Heredoc, redirect and var", "<< 'never   stop' c$A > $LOGFILE");
}
