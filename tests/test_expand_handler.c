/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:09:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 13:28:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern int	g_err_count;
extern t_hashtable	*g_symtab;

static int	test_wrapper(char *testname, char *test, char *expect)
{
	t_track	input;
	int		ret;
	bool	exec;

	printf("TEST: %s\n", testname);
	input.str = ft_strdup(test);
	input.pos = 0;
	exec = false;
	printf("String:\t|%s|\n", test);
	ft_expander(&input, g_symtab, &exec);
	printf("Result:\t|%s|\n", input.str);
	if (!ft_strncmp(input.str, expect, ft_strlen(input.str)))
	{
		printf(GREEN"OK\n\n"RESET);
		ret = 0;
	}
	else
	{
		printf(RED"Expect:\t|%s|\n\n"RESET, expect);
		ret = 1;
	}
	free(input.str);
	return (ret);
}

void	test_expand_handler(void)
{
	t_tkn_list	*head;

	head = NULL;
	printf(YELLOW"*******TEST_EXPAND_HANDLER*******\n\n"RESET);
	g_err_count = 0;
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	ft_new_node(&head, ft_strdup("<<"));
	ft_new_node(&head, ft_strdup("\"Hello        boy\""));
	ft_handle_heredoc(&head);
	printf("This is content: %s", head->content);

	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
