/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/14 21:03:23 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;

int	exec_expander(char *testname, char *test, char *expect, t_type type)
{
	t_track	input;
	int		ret;

	printf("TEST: %s\n", testname);
	printf("String:\t|%s|\n", test);
	ft_init_tracker(&input, ft_strdup(test), type);
	ft_expander(&input, g_symtab, type);
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

int	exec_expander_heredoc(char *name, char *test, char *expect)
{
	int		ret;
	char	*tmp;

	printf("TEST: %s\n", name);
	printf("String:\t|%s|\n", test);
	tmp = ft_strdup(test);
	ft_expander_heredoc(&tmp, g_symtab);
	printf("Result:\t|%s|\n", tmp);
	if (!ft_strncmp(tmp, expect, ft_strlen(expect) + 1))
	{
		printf(GREEN"OK\n\n"RESET);
		ret = 0;
	}
	else
	{
		printf(RED"Expect:\t|%s|\n\n"RESET, expect);
		ret = 1;
	}
	free(tmp);
	return (ret);
}

void	test_expand_tilde(t_type type)
{
	printf(BLUE"**\tTILDE\t**\n\n"RESET);
	g_err_count += exec_expander("no HOME set", "~", "~", type);

	ft_hashtable_insert(g_symtab, ft_strdup("HOME=/this/is/home"), 4, true);
	ft_hashtable_insert(g_symtab, ft_strdup("PWD=/this/is/PWD"), 3, true);
	ft_hashtable_insert(g_symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6, true);
	g_err_count += exec_expander("expand $HOME with ~", "~", "/this/is/home", type);
	g_err_count += exec_expander("expand $PWD with ~+", "~+", "/this/is/PWD", type);
	g_err_count += exec_expander("expand $OLDPWD with ~-", "~-", "/this/is/OLDPWD", type);

	g_err_count += exec_expander("tilde in assignment", "var=~", "var=/this/is/home", type);

}

void	test_expand_var(t_type type)
{
	printf(BLUE"**\tVARS\t**\n\n"RESET);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST='I am test'"), 4, true);
	g_err_count += exec_expander("simple var expansion", "$TEST", "'I am test'", type);
	g_err_count += exec_expander("double var", "$TEST$TEST", "'I am test''I am test'", type);
	g_err_count += exec_expander("empty var", "$NO_VAR", "", type);
	g_err_count += exec_expander("starting with number", "$1", "$1", type);
	g_err_count += exec_expander("no alnum at start", "$§", "$§", type);
	g_err_count += exec_expander("double quoted string after $", "$\"TEST\"", "TEST", type);
	g_err_count += exec_expander("double quoted $", "\"$\"TEST", "$TEST", type);
	g_err_count += exec_expander("double quoted var name", "\"$TEST\"ING", "'I am test'ING", type);
	g_err_count += exec_expander("single quoted string after $", "$'TEST'", "TEST", type);
	g_err_count += exec_expander("single quoted $", "'$'TEST", "$TEST", type);
	g_err_count += exec_expander("single quoted var name", "'$TEST'ING", "$TESTING", type);
	g_err_count += exec_expander("Two jointly quoted vars", "\"$TEST$TEST\"", "'I am test''I am test'", type);
	g_err_count += exec_expander("Two separatedly quoted vars", "\"$TEST\"\"$TEST\"", "'I am test''I am test'", type);

	g_status = 125;
	g_err_count += exec_expander("special var $?", "$?", "125", type);
}

void	test_expand_quotes(t_type type)
{
	printf(BLUE"**\tQUOTES\t**\n\n"RESET);
	g_err_count += exec_expander("single quoted string", "'Hallo'", "Hallo", type);
	g_err_count += exec_expander("double quoted string", "This:\"Hallo\"", "This:Hallo", type);
}

void	test_expand_combi(t_type type)
{
	printf(BLUE"**\tCOMBI\t**\n\n"RESET);
	g_err_count += exec_expander("Combination 1", "~/\"$TEST\"'betram'", "/this/is/home/'I am test'betram", type);
	g_err_count += exec_expander("Combination 2", "test=$?", "test=125", type);
	g_err_count += exec_expander("Combination 3", "~$NO_VAR$?", "~125", type);
}

void	test_expand_heredoc(void)
{
	printf(BLUE"**\tHEREDOC\t**\n\n"RESET);

	ft_hashtable_insert(g_symtab, ft_strdup("USER=gwolf"), 4, true);
	g_err_count += exec_expander_heredoc("Just a var", "Hello $USER", "Hello gwolf");
	g_err_count += exec_expander_heredoc("Quoted var", "This '$USER' is quoted", "This 'gwolf' is quoted");
	g_err_count += exec_expander_heredoc("Don't delete $", "$\"TEST\"", "$\"TEST\"");
	g_err_count += exec_expander_heredoc("Leaves just quotes", "\"$TEST\"", "\"\"");
	g_err_count += exec_expander_heredoc("Nothing changes", "\"$\"TEST", "\"$\"TEST");
}

void	test_expand_expander(void)
{
	printf(YELLOW"*******TEST_EXPAND*******\n\n"RESET);
	g_err_count = 0;
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	//test_expand_tilde(ARG);
	//test_expand_var(ARG);
	//test_expand_quotes(ARG);
	//test_expand_combi(ARG);
	test_expand_heredoc();
	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
