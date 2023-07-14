/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 13:29:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "expander.h"

void	tilde_empty(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: no HOME set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	tilde_normal(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: every $var is set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~+");
	printf("String = %s\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~-");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	tilde_assign(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: tilde in assignment\n");
	string = ft_strdup("var=~");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_normal(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: var normal\n");
	string = ft_strdup("$TEST");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_empty(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: var empty\n");
	string = ft_strdup("$NO");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	var_double(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: var double\n");
	string = ft_strdup("$TEST$TEST");
	printf("String = '%s'\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	quoted_str(t_hashtable *symtab)
{
	char	*string;

	printf("\n\tTEST: single quoted string\n");
	string = ft_strdup("'Hallo'");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: |%s|\n", string);
	free(string);
	printf("\n\tTEST: double quoted string\n");
	string = ft_strdup("This:\"Hallo\"");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: |%s|\n", string);
	free(string);
}

void	combined(t_hashtable *symtab)
{
	char	*string;

	printf("\n\tTEST: combine everything\n");
	string = ft_strdup("~/\"$TEST\"'betram'");
	printf("String = |%s|\n", string);
	ft_expand_expr(&string, symtab);
	printf("Result: |%s|\n", string);
	free(string);

}

void	test_expand(void)
{
	t_hashtable	*symtab;
	char		*string;

	printf("**\tTEST_EXPAND\t**\n");
	symtab = ft_hashtable_create(1, ft_hash_fnv1);
	tilde_empty(symtab);
	ft_hashtable_insert(symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	tilde_normal(symtab);
	tilde_assign(symtab);
	ft_hashtable_insert(symtab, ft_strdup("TEST='I am test'"), 4);
	var_normal(symtab);
	var_empty(symtab);
	var_double(symtab);
	quoted_str(symtab);
	combined(symtab);
	ft_hashtable_destroy(symtab);
}
