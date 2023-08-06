/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:09:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 21:11:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern int	g_err_count;
extern t_hashtable	*g_symtab;

void	exec_ft_handle_arg(void)
{
	t_tkn_list	*head;
	t_tkn_list	*tmp;

	head = NULL;
	tmp = NULL;
	ft_new_node(&head, ft_strdup("$TEST"));
	ft_new_node(&head, ft_strdup("\"Hello        boy\""));
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=no senor"), 4);
	tmp = head;
	ft_handle_arg(&tmp, g_symtab);
	test_print_tkn_list(head);
	ft_hashtable_delete(g_symtab, "TEST", 4);
	ft_free_lst(&head);
}

void	exec_ft_handle_heredoc(void)
{
	t_tkn_list	*head;
	t_tkn_list	*tmp;

	head = NULL;
	tmp = NULL;
	ft_new_node(&head, ft_strdup("<<"));
	ft_new_node(&head, ft_strdup("\"Hello        boy\""));
	tmp = head;
	ft_handle_heredoc(&tmp);
	test_print_tkn_list(head);
	ft_free_lst(&head);
}

void	exec_ft_handle_redirect(void)
{
	t_tkn_list	*head;
	t_tkn_list	*tmp;

	head = NULL;
	tmp = NULL;
	ft_new_node(&head, ft_strdup("<"));
	ft_new_node(&head, ft_strdup("$TES"));
	tmp = head;
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=no senor"), 4);
	ft_handle_redirect(&tmp, g_symtab);
	test_print_tkn_list(head);
	ft_hashtable_delete(g_symtab, "TEST", 4);
	ft_free_lst(&head);
}

void	test_expand_handler(void)
{

	printf(YELLOW"*******TEST_EXPAND_HANDLER*******\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	exec_ft_handle_heredoc();
	exec_ft_handle_redirect();
	exec_ft_handle_arg();

	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
