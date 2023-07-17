/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/17 20:04:41 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char			*string;
extern t_hashtable	*symtab;
extern t_info		info;

void	exec_expand(char *testname, char *test)
{
	printf("TEST: %s\n", testname);
	string = ft_strdup(test);
	printf("String:\t|%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result:\t|%s|\n\n", string);
	free(string);
}

void	test_expand(void)
{
	printf("**\tTEST_EXPAND\t**\n");
	symtab = ft_hashtable_create(1, ft_hash_fnv1);

	exec_expand("no HOME set", "~");

	ft_hashtable_insert(symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	exec_expand("expand $HOME with ~", "~");
	exec_expand("expand $PWD with ~+", "~+");
	exec_expand("expand $OLDPWD with ~-", "~-");

	exec_expand("tilde in assignment", "var=~");

	ft_hashtable_insert(symtab, ft_strdup("TEST='I am test'"), 4);
 	exec_expand("simple var expansion", "$TEST");
	exec_expand("double var", "$TEST$TEST");
	exec_expand("empty var", "$NO_VAR");
	exec_expand("no var name", "$1");

	info.ret_code = 125;
	info.shell_name = "/bin/shell";
	exec_expand("special var $?", "$?");
	exec_expand("special var $0", "$0");

	exec_expand("single quoted string", "'Hallo'");
	exec_expand("double quoted string", "This:\"Hallo\"");

	exec_expand("Combination 1", "~/\"$TEST\"'betram'");
	exec_expand("Combination 2", "test=$?");
	exec_expand("Combination 3", "~$test$0$?");

	ft_hashtable_destroy(symtab);
}
