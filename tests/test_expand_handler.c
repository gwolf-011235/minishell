/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:09:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/11 11:18:26 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern int			g_err_count;
extern t_hashtable	*g_symtab;
extern t_tkn_list	*g_head;

void	exec_ft_handle_arg(char *testname, char *str)
{
	t_tkn_list	*tmp;

	printf("TEST: %s\n", testname);
	printf("Input: %s\n\n", str);
	ft_lex_input(&g_head, str);
	tmp = g_head;
	ft_expand_arg(&tmp, g_symtab);
	g_head = ft_list_first(tmp);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	exec_ft_handle_heredoc(char *testname, char *str)
{
	t_tkn_list	*tmp;

	printf("TEST: %s\n", testname);
	printf("Input: %s\n\n", str);
	ft_lex_input(&g_head, str);
	tmp = g_head;
	ft_expand_heredoc(&tmp);
	g_head = ft_list_first(tmp);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	exec_ft_handle_redirect(char *testname, char *str)
{
	t_tkn_list	*tmp;

	printf("TEST: %s\n", testname);
	printf("Input: %s\n\n", str);
	ft_lex_input(&g_head, str);
	tmp = g_head;
	ft_expand_redirect(&tmp, g_symtab);
	g_head = ft_list_first(tmp);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	test_handle_arg(void)
{
	printf(BLUE"**\tft_handle_arg\t**\n\n"RESET);
	exec_ft_handle_arg("Var to expand and stuff after", "$TEST\"Hello      boy\"");
	exec_ft_handle_arg("empty var", "$NOEXIST");
	exec_ft_handle_arg("empty var but quoted", "\"$NOEXIST\"");
	exec_ft_handle_arg("empty var, second quoted", "$NOEXIST\"$NOEXIST\"");
	exec_ft_handle_arg("Var to expand", "$TEST");
	exec_ft_handle_arg("Don't split but rm quotes", "'I     no    split' \"Me   neither\"");
	exec_ft_handle_arg("Don't split but rm quotes 2", "\"Me   neither\"");
	exec_ft_handle_arg("Spicy expand", "l$S");
	exec_ft_handle_arg("Single quote after expand", "$SINGLE");
	exec_ft_handle_arg("Stuff before, empty, expand after", "stuff$A$TEST");
	exec_ft_handle_arg("Expand, empty, expand", "$TEST$A$TEST");
}

void	test_handle_heredoc(void)
{
	printf(BLUE"**\tft_handle_heredoc\t**\n\n"RESET);
	exec_ft_handle_heredoc("Remove quotes", "<< 'ahoy'");
	exec_ft_handle_heredoc("Remove double quotes", "<< \"matey\"");
	exec_ft_handle_heredoc("Remove double and single quotes", "<< \"\"shipmen''");
}

void	test_handle_redirect(void)
{
	printf(BLUE"**\tft_handle_redirect\t**\n\n"RESET);
	exec_ft_handle_redirect("Var to expand", "< $TEST");
	exec_ft_handle_redirect("Ambiguous redirect", "> $NOEXIST");
	exec_ft_handle_redirect("Quoted", ">> \"Hello    World\"");
	exec_ft_handle_redirect("Empty quotes", "< \"\"");
	exec_ft_handle_redirect("Double var, one quoted", "> $TEST\"$TEST\"");
	exec_ft_handle_redirect("Double empty var, one quoted", "> $NOEXIST\"$NOEXIST\"");
	exec_ft_handle_redirect("Triple empty var", "<$NO$NJET$NADA");
}

void	test_expand_handler(void)
{
	printf(YELLOW"*******TEST_EXPAND_HANDLER*******\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=I   have    spaces"), 4);
	ft_hashtable_insert(g_symtab, ft_strdup("S=s -la"), 1);
	ft_hashtable_insert(g_symtab, ft_strdup("SINGLE=badboy'"), 6);

	test_handle_arg();
	test_handle_heredoc();
	test_handle_redirect();

	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
