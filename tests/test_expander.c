/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:43:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/13 21:40:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_error	ft_expand_words(char **word, t_hashtable *symtab);

void	test_expand_empty(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: no HOME set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_words(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	test_expand_normal(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: every $var is set\n");
	string = ft_strdup("~");
	printf("String = '%s'\n", string);
	ft_expand_words(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~+");
	printf("String = %s\n", string);
	ft_expand_words(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
	string = ft_strdup("~-");
	printf("String = '%s'\n", string);
	ft_expand_words(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	test_expand_assign(t_hashtable *symtab)
{
	char	*string;

	printf("\tTEST: tilde in assignment\n");
	string = ft_strdup("var=~");
	printf("String = '%s'\n", string);
	ft_expand_words(&string, symtab);
	printf("Result: '%s'\n", string);
	free(string);
}

void	test_expand(void)
{
	t_hashtable	*symtab;
	char		*string;

	printf("**\tTEST_EXPAND\t**\n");
	symtab = ft_hashtable_create(1, ft_hash_fnv1);
	test_expand_empty(symtab);
	ft_hashtable_insert(symtab, ft_strdup("HOME=/this/is/home"), 4);
	ft_hashtable_insert(symtab, ft_strdup("PWD=/this/is/PWD"), 3);
	ft_hashtable_insert(symtab, ft_strdup("OLDPWD=/this/is/OLDPWD"), 6);
	test_expand_normal(symtab);
	test_expand_assign(symtab);
	ft_hashtable_destroy(symtab);
}
