/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 12:07:11 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;

static int	test_wrapper(char *testname, char *test, char *expect)
{
	int		ret;
	bool	exec;

	printf("TEST: %s\n", testname);
	g_string = ft_strdup(test);
	exec = false;
	printf("String:\t|%s|\n", test);
	ft_expander(&g_string, g_symtab, &exec);
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
	g_err_count += test_wrapper("no HOME set", "~", "~");

	ft_hashtable_insert(g_symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(g_symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(g_symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	g_err_count += test_wrapper("expand $HOME with ~", "~", "/this/is/home");
	g_err_count += test_wrapper("expand $PWD with ~+", "~+", "/this/is/PWD");
	g_err_count += test_wrapper("expand $OLDPWD with ~-", "~-", "/this/is/OLDPWD");

	g_err_count += test_wrapper("tilde in assignment", "var=~", "var=/this/is/home");

}

void	test_expand_var(void)
{
	printf(BLUE"**\tVARS\t**\n\n"RESET);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST='I am test'"), 4);
	g_err_count += test_wrapper("simple var expansion", "$TEST", "'I am test'");
	g_err_count += test_wrapper("double var", "$TEST$TEST", "'I am test''I am test'");
	g_err_count += test_wrapper("empty var", "$NO_VAR", "");
	g_err_count += test_wrapper("starting with number", "$1", "$1");
	g_err_count += test_wrapper("no alnum at start", "$§", "$§");
	g_err_count += test_wrapper("double quoted string after $", "$\"TEST\"", "\"TEST\"");
	g_err_count += test_wrapper("double quoted $", "\"$\"TEST", "\"$\"TEST");
	g_err_count += test_wrapper("double quoted var name", "\"$TEST\"ING", "\"'I am test'\"ING");
	g_err_count += test_wrapper("single quoted string after $", "$'TEST'", "'TEST'");
	g_err_count += test_wrapper("single quoted $", "'$'TEST", "'$'TEST");
	g_err_count += test_wrapper("single quoted var name", "'$TEST'ING", "'$TEST'ING");

	g_status = 125;
	g_err_count += test_wrapper("special var $?", "$?", "125");
}

void	test_expand_quotes(void)
{
	printf(BLUE"**\tQUOTES\t**\n\n"RESET);
	g_err_count += test_wrapper("single quoted string", "'Hallo'", "Hallo");
	g_err_count += test_wrapper("double quoted string", "This:\"Hallo\"", "This:Hallo");
}

void	test_expand_combi(void)
{
	printf(BLUE"**\tCOMBI\t**\n\n"RESET);
	g_err_count += test_wrapper("Combination 1", "~/\"$TEST\"'betram'", "/this/is/home/'I am test'betram");
	g_err_count += test_wrapper("Combination 2", "test=$?", "test=125");
	g_err_count += test_wrapper("Combination 3", "~$NO_VAR$0$?", "~/bin/shell125");
}


void	test_expand_expander(void)
{
	printf(YELLOW"*******TEST_EXPAND*******\n\n"RESET);
	g_err_count = 0;
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_expand_tilde();
	test_expand_var();
	//test_expand_quotes();
	//test_expand_combi();
	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
