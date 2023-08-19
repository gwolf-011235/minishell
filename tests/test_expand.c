/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:58:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 12:44:18 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;
extern t_tkn_list	*g_head;

void	exec_expand_tkn_lst(char *testname, char *str, t_buf *buf)
{
	printf("TEST: %s\n", testname);
	printf("Input: %s\n\n", str);
	ft_lex_input(&g_head, str, buf);
	ft_expand_tkn_lst(&g_head, g_symtab, buf);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	test_expand_list(void)
{
	int			i;
	t_tkn_list	*tmp;
	t_buf		buf;

	printf(YELLOW"*******TEST_EXPAND_TKN_LIST*******\n\n"RESET);
	ft_buf_init(&buf);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	ft_hashtable_insert(g_symtab, "TEST=USER    SPACEMAN", 4, true);
	ft_hashtable_insert(g_symtab, "A=at -e", 1, true);
	ft_hashtable_insert(g_symtab, "LOGFILE=/usr/log/logfile.txt", 7, true);
	ft_hashtable_insert(g_symtab, "HOME=/usr/home", 4, true);
	//HEREDOC
	exec_expand_tkn_lst("Heredoc quote removal", "<< 'hello' cat", &buf);
	//REDIRECT
	exec_expand_tkn_lst("Redirect expand", "echo blub > $TEST", &buf);
	exec_expand_tkn_lst("Redirect Ambiguous", "echo blub > $NOEXIST", &buf);
	exec_expand_tkn_lst("Redirect Empty string", "echo blub > \"$NOEXIST\"", &buf);
	exec_expand_tkn_lst("Redirect tilde start", "echo blub > ~/dir/log", &buf);
	exec_expand_tkn_lst("Redirect tilde mid", "echo blub > no/expand/pls/~/dir/log", &buf);
	//ASSIGN
	exec_expand_tkn_lst("Assign expand", "VAR=$TEST", &buf);
	exec_expand_tkn_lst("Assign no exist", "VAR=$NOEXIST", &buf);
	exec_expand_tkn_lst("Assign in heredoc", "<< VAR=$TEST", &buf);
	exec_expand_tkn_lst("Arg, Assign, Assign", "export VAR=$TEST _VAR2=String", &buf);
	exec_expand_tkn_lst("Assign, Arg, Assign", "VAR=$TEST export _VAR2=String", &buf);
	exec_expand_tkn_lst("Assign with tilde", "VAR=~/test", &buf);
	exec_expand_tkn_lst("Assign with tilde mid", "VAR=no/expand/~/test", &buf);
	//VAR
	exec_expand_tkn_lst("Var expand", "Hello $TEST", &buf);
	exec_expand_tkn_lst("Var no exist", "$NOEXIST", &buf);
	exec_expand_tkn_lst("Var multiple expand", "Hello$TEST\"$NOEXIST\"yada\"   \"sisi", &buf);
	exec_expand_tkn_lst("Var Expand then no expand", "\"$TEST\"$1", &buf);
	exec_expand_tkn_lst("Var expand, then empty then var", "\"$TEST\"$NOEXIST$TEST", &buf);
	exec_expand_tkn_lst("Var with tilde", "Hello ~", &buf);
	//Multiple
	exec_expand_tkn_lst("Heredoc, redirect and var", "<< 'never   stop' c$A > $LOGFILE", &buf);
}
