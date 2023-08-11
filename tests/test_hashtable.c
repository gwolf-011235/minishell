/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 21:00:21 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

void	test_hashtable(void)
{
	t_hashtable	*sym_tab;
	t_env_var	*env_var;

	sym_tab = ft_hashtable_create(100, ft_hash_fnv1);

	ft_hashtable_insert(sym_tab, ft_strdup("TEST=Ima testing"), 4);
	env_var = ft_hashtable_lookup(sym_tab, "TEST", 4);
	if (env_var == NULL)
		printf("not found\n");
	else
		printf("TEST was found\n");
	ft_hashtable_delete(sym_tab, "TEST", 4);
	ft_hashtable_destroy(sym_tab);
}