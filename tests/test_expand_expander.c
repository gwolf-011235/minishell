/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 19:57:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;

typedef t_err	(*funptr_expand_t)(t_track *input, t_hashtable *symtab, t_type type);

int	exec_expand(char *testname, char *test, char *expect, funptr_expand_t funptr_expand)
{
	t_track	input;
	int		ret;

	printf("TEST: %s\n", testname);
	printf("String:\t|%s|\n", test);
	ft_init_tracker(&input, ft_strdup(test));
	funptr_expand(&input, g_symtab, ARG);
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

void	test_expand_tilde(funptr_expand_t funptr_expand)
{
	printf(BLUE"**\tTILDE\t**\n\n"RESET);
	g_err_count += exec_expand("no HOME set", "~", "~", funptr_expand);

	ft_hashtable_insert(g_symtab, ft_strdup("HOME=/this/is/home"), 4, true);
	ft_hashtable_insert(g_symtab, ft_strdup("PWD=/this/is/PWD"), 3, true);
	ft_hashtable_insert(g_symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6, true);
	g_err_count += exec_expand("expand $HOME with ~", "~", "/this/is/home", funptr_expand);
	g_err_count += exec_expand("expand $PWD with ~+", "~+", "/this/is/PWD", funptr_expand);
	g_err_count += exec_expand("expand $OLDPWD with ~-", "~-", "/this/is/OLDPWD", funptr_expand);

	//g_err_count += exec_expand("tilde in assignment", "var=~", "var=/this/is/home", funptr_expand);

}

void	test_expand_var(funptr_expand_t funptr_expand)
{
	printf(BLUE"**\tVARS\t**\n\n"RESET);
	ft_hashtable_insert(g_symtab, ft_strdup("TEST='I am test'"), 4, true);
	g_err_count += exec_expand("simple var expansion", "$TEST", "'I am test'", funptr_expand);
	g_err_count += exec_expand("double var", "$TEST$TEST", "'I am test''I am test'", funptr_expand);
	g_err_count += exec_expand("empty var", "$NO_VAR", "", funptr_expand);
	g_err_count += exec_expand("starting with number", "$1", "$1", funptr_expand);
	g_err_count += exec_expand("no alnum at start", "$§", "$§", funptr_expand);
	g_err_count += exec_expand("double quoted string after $", "$\"TEST\"", "TEST", funptr_expand);
	g_err_count += exec_expand("double quoted $", "\"$\"TEST", "$TEST", funptr_expand);
	g_err_count += exec_expand("double quoted var name", "\"$TEST\"ING", "'I am test'ING", funptr_expand);
	g_err_count += exec_expand("single quoted string after $", "$'TEST'", "TEST", funptr_expand);
	g_err_count += exec_expand("single quoted $", "'$'TEST", "$TEST", funptr_expand);
	g_err_count += exec_expand("single quoted var name", "'$TEST'ING", "$TESTING", funptr_expand);
	g_err_count += exec_expand("Two jointly quoted vars", "\"$TEST$TEST\"", "'I am test''I am test'", funptr_expand);
	g_err_count += exec_expand("Two separatedly quoted vars", "\"$TEST\"\"$TEST\"", "'I am test''I am test'", funptr_expand);

	g_status = 125;
	g_err_count += exec_expand("special var $?", "$?", "125", funptr_expand);
}

void	test_expand_quotes(funptr_expand_t funptr_expand)
{
	printf(BLUE"**\tQUOTES\t**\n\n"RESET);
	g_err_count += exec_expand("single quoted string", "'Hallo'", "Hallo", funptr_expand);
	g_err_count += exec_expand("double quoted string", "This:\"Hallo\"", "This:Hallo", funptr_expand);
}

void	test_expand_combi(funptr_expand_t funptr_expand)
{
	printf(BLUE"**\tCOMBI\t**\n\n"RESET);
	g_err_count += exec_expand("Combination 1", "~/\"$TEST\"'betram'", "/this/is/home/'I am test'betram", funptr_expand);
	g_err_count += exec_expand("Combination 2", "test=$?", "test=125", funptr_expand);
	g_err_count += exec_expand("Combination 3", "~$NO_VAR$?", "~125", funptr_expand);
}

void	test_expand_expander(void)
{
	printf(YELLOW"*******TEST_EXPAND*******\n\n"RESET);
	g_err_count = 0;
	g_symtab = ft_hashtable_create(1, ft_hash_fnv1);
	//test_expand_tilde(ft_expander_full);
	//test_expand_var(ft_expander_full);
	//test_expand_quotes(ft_expander_full);
	//test_expand_combi(ft_expander_full);
	//test_expand_tilde(ft_expander_arg);
	test_expand_var(ft_expander_arg);
	//test_expand_quotes(ft_expander_arg);
	//test_expand_combi(ft_expander_arg);
	if (g_err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, g_err_count);
	ft_hashtable_destroy(g_symtab);
}
