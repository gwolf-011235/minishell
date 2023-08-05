/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:09:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 14:51:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern int	g_err_count;
extern t_hashtable	*g_symtab;

void	exec_ft_handle_heredoc(void)
{
	t_tkn_list	*head;

	head = NULL;
	ft_new_node(&head, ft_strdup("<<"));
	ft_new_node(&head, ft_strdup("\"Hello        boy\""));
	ft_handle_heredoc(&head);
	printf("This is content: %s\n", head->content);
	ft_free_lst(&head);
}

void	exec_ft_handle_redirect(void)
{
	t_tkn_list	*head;

	head = NULL;
	ft_new_node(&head, ft_strdup("<"));
	ft_new_node(&head, ft_strdup("$TEST"));
	ft_hashtable_insert(g_symtab, ft_strdup("TEST=hi"), 4);
	ft_handle_redirect(&head, g_symtab);
	printf("This is content: %s\n", head->content);
	ft_hashtable_delete(g_symtab, "TEST", 4);
	ft_free_lst(&head);
}

void	test_expand_handler(void)
{

	printf(YELLOW"*******TEST_EXPAND_HANDLER*******\n\n"RESET);
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	exec_ft_handle_heredoc();
	exec_ft_handle_redirect();

	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
