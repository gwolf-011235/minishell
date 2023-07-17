/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/17 21:01:50 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char			*string;
extern t_hashtable	*symtab;
extern t_info		info;

int	exec_expand(char *testname, char *test, char *expect)
{
	int	ret;

	printf("TEST: %s\n", testname);
	string = ft_strdup(test);
	printf("String:\t|%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result:\t|%s|\n", string);
	if (!ft_strcmp(string, expect))
	{
		printf(GREEN"OK\n\n"RESET);
		ret = 0;
	}
	else
	{
		printf(RED"Expect:\t|%s|\n\n"RESET, expect);
		ret = 1;
	}
	free(string);
	return (ret);
}

void	test_expand(void)
{
	int	err_count;

	printf(YELLOW"*******TEST_EXPAND*******\n\n"RESET);
	err_count = 0;
	symtab = ft_hashtable_create(1, ft_hash_fnv1);

	printf(BLUE"**\tTILDE\t**\n\n"RESET);
	err_count += exec_expand("no HOME set", "~", "~");

	ft_hashtable_insert(symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	err_count += exec_expand("expand $HOME with ~", "~", "/this/is/home");
	err_count += exec_expand("expand $PWD with ~+", "~+", "/this/is/PWD");
	err_count += exec_expand("expand $OLDPWD with ~-", "~-", "/this/is/OLDPWD");

	err_count += exec_expand("tilde in assignment", "var=~", "var=/this/is/home");

	printf(BLUE"**\tVARS\t**\n\n"RESET);
	ft_hashtable_insert(symtab, ft_strdup("TEST='I am test'"), 4);
	err_count += exec_expand("simple var expansion", "$TEST", "'I am test'");
	err_count += exec_expand("double var", "$TEST$TEST", "'I am test''I am test'");
	err_count += exec_expand("empty var", "$NO_VAR", "");
	err_count += exec_expand("no alpha or underscore", "$1", "$1");
	err_count += exec_expand("quoted string after $", "$\"TEST\"", "TEST");
	err_count += exec_expand("quoted $", "\"$\"TEST", "$TEST");
	err_count += exec_expand("quoted var name", "\"$TEST\"ING", "'I am test'ING");

	info.ret_code = 125;
	info.shell_name = "/bin/shell";
	err_count += exec_expand("special var $?", "$?", "125");
	err_count += exec_expand("special var $0", "$0", "/bin/shell");

	printf(BLUE"**\tQUOTES\t**\n\n"RESET);
	err_count += exec_expand("single quoted string", "'Hallo'", "Hallo");
	err_count += exec_expand("double quoted string", "This:\"Hallo\"", "This:Hallo");

	printf(BLUE"**\tCOMBI\t**\n\n"RESET);
	err_count += exec_expand("Combination 1", "~/\"$TEST\"'betram'", "/this/is/home/'I am test'betram");
	err_count += exec_expand("Combination 2", "test=$?", "test=125");
	err_count += exec_expand("Combination 3", "~$NO_VAR$0$?", "~/bin/shell125");

	if (err_count > 0)
		printf(RED"ERRORS: %d\n"RESET, err_count);
	ft_hashtable_destroy(symtab);
}
