/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:40:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 13:58:19 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/* Globals for testing */

t_data		g_data;
char		*g_string;
t_hashtable	*g_symtab;
char		**g_envp;
int			g_err_count;
t_tkn_list	*g_head;
char		**g_argv;

__sig_atomic_t	g_status;

void	test_setup_data(void)
{
	ft_env_setup(&g_data.env_table);
	g_head = NULL;
}

void	test_teardown_data(void)
{
	ft_hashtable_destroy(g_data.env_table);
}

void	test_setup_argv(size_t size)
{
	g_argv = malloc(sizeof(char *) * size);
}

void	test_teardown_argv(void)
{
	free(g_argv);
	g_argv = NULL;
}

void	test_print_t_type(t_type type)
{
	char	*str;

	if (type == ARG)
		str = "ARG";
	else if (type == INFILE)
		str = "INFILE";
	else if (type == HEREDOC)
		str = "HEREDOC";
	else if (type == OUTFILE)
		str = "OUTFILE";
	else if (type == APPEND)
		str = "APPEND";
	else if (type == PIPE)
		str = "PIPE";
	else if (type == NEWL)
		str = "NEWLINE";
	else if (type == AMBIGUOUS)
		str = "AMBIGUOUS";
	else if (type == DELETE)
		str = "DELETE";
	else if (type == ASSIGN)
		str = "ASSIGN";
	printf("   Type:\t%s\n", str);
}

void	test_print_tkn_list(t_tkn_list *head)
{
	int	i;

	i = 0;
	printf("** Token list **\n");
	while (head)
	{
		i++;
		printf("-> %d\n", i);
		printf("   String:\t%s\n", head->content);
		test_print_t_type(head->type);
		head = head->next;
	}
	printf("-> NULL\n\n");
}

void	test_print_str_array(char **array)
{
	int	i;

	i = 0;
	if (array[0] == NULL)
		printf("EMPTY\n");
	while (array[i])
	{
		printf("%i: %s\n", i, array[i]);
		i++;
	}
}

int	main(void)
{
	//test_buffer();
	//test_hashtable();
	//test_replace_token();
	//test_prompt();
	//test_check_syntax();
	//test_env_envp();
	//test_lexer();
	//test_expand_list();
	test_expand_expander();
	//test_expand_field_split();
	//test_expand_handler();
	//test_parser();
	test_executor();
	//test_builtin_echo();
	//test_builtin_cd();
	//test_builtin_pwd();
	//test_builtin_export();
	//test_builtin_unset();
	//test_builtin_env();
	//test_builtin_exit();
	return (0);
}
