/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:40:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 13:26:24 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_data		g_data;
char		*g_string;
t_hashtable	*g_symtab;
char		**g_envp;
t_info		g_info;
int			g_err_count;
t_tkn_list	*lst_head;
char		**g_argv;

void	test_setup_data(void)
{
	ft_env_setup(&g_data.env_table);
	lst_head = NULL;
	g_data.info.shell_name = "/bin/minishell";
	g_data.info.ret_code = 255;
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

int	main(void)
{
	//test_hashtable();
	//test_replace_token();
	//test_prompt();
	//test_check_syntax();
	//test_env_envp();
	//test_expand();
	//test_lexer();
	//test_expand_list();
	//test_builtin_echo();
	//test_builtin_cd();
	//test_builtin_pwd();
	//test_builtin_export();
	test_builtin_unset();
	return (0);
}
