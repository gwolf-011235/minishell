/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 19:48:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;
/**
 * @brief Pretty print all elements.
 *
 * Print starting string.
 * Print all elements at each index. Every element is denoted by a "->".
 * If more than one element is at a given index they get separated by newline.
 * Print number of elements.
 * Print end string.
 * @param ht Hashtable to print.
 */
void	test_hashtable_pretty_print(t_hashtable *ht)
{
	uint32_t	i;
	t_env_var	*tmp;

	printf("Start Table\n");
	i = 0;
	while (i < ht->size)
	{
		if (ht->elements[i] == NULL)
			printf("%i\n---\n", i);
		else
		{
			printf("%i\n", i);
			tmp = ht->elements[i];
			while (tmp != NULL)
			{
				printf("->\t%s\n", tmp->env_string);
				tmp = tmp->next;
			}
		}
		i++;
	}
	printf("Number of elements: %d\n", ht->num_elements);
	printf("End Table\n");
}

void	test_insert_one(char *name, char *env_str, size_t keylen, bool has_value)
{
	t_env_var	*env_var;

 	printf("TEST: %s\n", name);
	ft_hashtable_insert(g_symtab, ft_strdup(env_str), keylen, has_value);
	env_var = ft_hashtable_lookup(g_symtab, env_str, keylen);
	if (env_var == NULL)
		printf("Var was not found\n");
	else
	{
		printf("Var was found!\n");
		printf("String:\t%s\nValue:\t%s\n", env_var->env_string, env_var->value);
	}
	ft_hashtable_delete(g_symtab, env_str, keylen);
}

void	test_hashtable(void)
{

	g_symtab = ft_hashtable_create(100, ft_hash_fnv1);
	test_insert_one("Simple insert", "TEST=I am test", 4, true);
	test_insert_one("No value", "NOVAL=", 5, true);
	test_insert_one("No equals", "OHNO", 4, false);

	ft_hashtable_destroy(g_symtab);
}