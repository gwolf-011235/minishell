/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 18:23:39 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern char			*string;
extern t_hashtable	*symtab;
extern t_info		info;

void	tilde_empty(void)
{
	printf("\tTEST: no HOME set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	tilde_normal(void)
{
	printf("\tTEST: every $var is set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~+");
	printf("String = %s\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~-");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	tilde_assign(void)
{
	printf("\tTEST: tilde in assignment\n");
	string = ft_strdup("var=~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_normal(void)
{
	printf("\tTEST: var normal\n");
	string = ft_strdup("$TEST");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_empty(void)
{
	printf("\tTEST: var empty\n");
	string = ft_strdup("$NO");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_double(void)
{
	printf("\tTEST: var double\n");
	string = ft_strdup("$TEST$TEST");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_special(void)
{
	printf("\n\tTEST: var special\n");
	string = ft_strdup("$?");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("$0");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: '%s'\n", string);
	free(string);
}

void	quoted_str(void)
{
	printf("\n\tTEST: single quoted string\n");
	string = ft_strdup("'Hallo'");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: |%s|\n", string);
	free(string);
	printf("\n\tTEST: double quoted string\n");
	string = ft_strdup("This:\"Hallo\"");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: |%s|\n", string);
	free(string);
}

void	combined(void)
{
	printf("\n\tTEST: combine everything\n");
	string = ft_strdup("~/\"$TEST\"'betram'");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: |%s|\n", string);
	free(string);
	string = ft_strdup("test=$?");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: |%s|\n", string);
	free(string);
	string = ft_strdup("~$test$0$?");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab, &info);
	printf("Result: |%s|\n", string);
	free(string);
}

void	test_expand(void)
{
	printf("**\tTEST_EXPAND\t**\n");
	symtab = ft_hashtable_create(1, ft_hash_fnv1);
	info.ret_code = 125;
	info.shell_name = "/bin/shell";
	tilde_empty();
	ft_hashtable_insert(symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	tilde_normal();
	tilde_assign();
	ft_hashtable_insert(symtab, ft_strdup("TEST='I am test'"), 4);
	var_normal();
	var_empty();
	var_double();
	var_special();
	quoted_str();
	combined();
	ft_hashtable_destroy(symtab);
}
