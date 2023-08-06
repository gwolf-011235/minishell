/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:09:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 18:10:00 by gwolf            ###   ########.fr       */
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
	ft_handle_arg(&tmp, g_symtab);
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
	ft_handle_heredoc(&tmp);
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
	ft_handle_redirect(&tmp, g_symtab);
	g_head = ft_list_first(tmp);
	test_print_tkn_list(g_head);
	ft_free_lst(&g_head);
}

void	test_expand_handler(void)
{
	printf(YELLOW"*******TEST_EXPAND_HANDLER*******\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	printf(BLUE"**\tft_handle_arg\t**\n\n"RESET);
	exec_ft_handle_arg("empty var", "$TEST");
	//exec_ft_handle_heredoc();
	//exec_ft_handle_redirect();
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=I   have    spaces"), 4);
	exec_ft_handle_arg("Var to expand", "$TEST");
	exec_ft_handle_arg("Var to expand and stuff after", "$TEST \"Hello      boy\"");
	exec_ft_handle_arg("Don't split but rm quotes", "'I     no    split' \"Me   neither\"");
	exec_ft_handle_arg("Don't split but rm quotes 2", "\"Me   neither\"");
	ft_hashtable_insert(g_symtab, ft_strdup("S=s -la"), 1);
	exec_ft_handle_arg("Spicy expand", "l$S");

	printf(BLUE"**\tft_handle_heredoc\t**\n\n"RESET);
	exec_ft_handle_heredoc("Remove quotes", "<< 'ahoy'");

	printf(BLUE"**\tft_handle_redirect\t**\n\n"RESET);
	exec_ft_handle_redirect("Var to expand", "< $TEST");
	exec_ft_handle_redirect("Ambiguous redirect", "> $NOEXIST");
	exec_ft_handle_redirect("Quoted", ">> \"Hello    World\"");

	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
