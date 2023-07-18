/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/18 03:16:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "lexer_list.h"
#include "lexer_tok.h"

t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern t_info		g_info;
extern int			g_err_count;

int	wrapper_ft_expand_expr(char *testname, char *test, char *expect)
{
	int	ret;

	printf("TEST: %s\n", testname);
	g_string = ft_strdup(test);
	printf("String:\t|%s|\n", g_string);
	ft_expand_expr(&g_string, g_symtab, &g_info);
	printf("Result:\t|%s|\n", g_string);
	if (!ft_strncmp(g_string, expect, ft_strlen(g_string)))
	{
		printf(GREEN"OK\n\n"RESET);
		ret = 0;
	}
	else
	{
		printf(RED"Expect:\t|%s|\n\n"RESET, expect);
		ret = 1;
	}
	free(g_string);
	return (ret);
}

void	test_expand_tilde(void)
{
	printf(BLUE"**\tTILDE\t**\n\n"RESET);
	g_err_count += wrapper_ft_expand_expr("no HOME set", "~", "~");

	ft_hashtable_insert(g_symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(g_symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	g_err_count += wrapper_ft_expand_expr("expand $HOME with ~", "~", "/this/is/home");
	g_err_count += wrapper_ft_expand_expr("expand $PWD with ~+", "~+", "/this/is/PWD");
	g_err_count += wrapper_ft_expand_expr("expand $OLDPWD with ~-", "~-", "/this/is/OLDPWD");

	g_err_count += wrapper_ft_expand_expr("tilde in assignment", "var=~", "var=/this/is/home");

}

void	test_expand_var(void)
{
	printf(BLUE"**\tVARS\t**\n\n"RESET);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST='I am test'"), 4);
	g_err_count += wrapper_ft_expand_expr("simple var expansion", "$TEST", "'I am test'");
	g_err_count += wrapper_ft_expand_expr("double var", "$TEST$TEST", "'I am test''I am test'");
	g_err_count += wrapper_ft_expand_expr("empty var", "$NO_VAR", "");
	g_err_count += wrapper_ft_expand_expr("starting with number", "$1", "");
	g_err_count += wrapper_ft_expand_expr("no alnum at start", "$§", "$§");
	g_err_count += wrapper_ft_expand_expr("double quoted string after $", "$\"TEST\"", "TEST");
	g_err_count += wrapper_ft_expand_expr("double quoted $", "\"$\"TEST", "$TEST");
	g_err_count += wrapper_ft_expand_expr("double quoted var name", "\"$TEST\"ING", "'I am test'ING");
	g_err_count += wrapper_ft_expand_expr("single quoted string after $", "$'TEST'", "TEST");
	g_err_count += wrapper_ft_expand_expr("single quoted $", "'$'TEST", "$TEST");
	g_err_count += wrapper_ft_expand_expr("single quoted var name", "'$TEST'ING", "$TESTING");

	g_info.ret_code = 125;
	g_info.shell_name = "/bin/shell";
	g_err_count += wrapper_ft_expand_expr("special var $?", "$?", "125");
	g_err_count += wrapper_ft_expand_expr("special var $0", "$0", "/bin/shell");
}

void	test_expand_quotes(void)
{
	printf(BLUE"**\tQUOTES\t**\n\n"RESET);
	g_err_count += wrapper_ft_expand_expr("single quoted string", "'Hallo'", "Hallo");
	g_err_count += wrapper_ft_expand_expr("double quoted string", "This:\"Hallo\"", "This:Hallo");
}

void	test_expand_combi(void)
{
	printf(BLUE"**\tCOMBI\t**\n\n"RESET);
	g_err_count += wrapper_ft_expand_expr("Combination 1", "~/\"$TEST\"'betram'", "/this/is/home/'I am test'betram");
	g_err_count += wrapper_ft_expand_expr("Combination 2", "test=$?", "test=125");
	g_err_count += wrapper_ft_expand_expr("Combination 3", "~$NO_VAR$0$?", "~/bin/shell125");
}

void	test_expand_list(void)
{
	int			i;
	t_tkn_list	*tmp;

	i = 1;
	g_data.lst_head = NULL;
	g_data.env_table = g_symtab;
	printf(BLUE"**\tLIST\t**\n\n"RESET);
	g_string = "~ $TEST\n";
	ft_list_token(&g_data, g_string);
	ft_expand_tkn_lst(g_data.lst_head, &g_data);
	tmp = g_data.lst_head;
	while (tmp)
	{
		if (!strncmp(tmp->content, "\n", ft_strlen(tmp->content)))
			printf("%d: newline\n", i);
		else
			printf("%d: %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}

}

void	test_expand(void)
{
	printf(YELLOW"*******TEST_EXPAND*******\n\n"RESET);
	g_err_count = 0;
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_expand_tilde();
	test_expand_var();
	test_expand_quotes();
	test_expand_combi();
	test_expand_list();
	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
