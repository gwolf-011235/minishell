/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:39 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/28 17:54:09 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hashtable_print.c
 * @brief Functions to print out env hashtable
 */
#include "hashtable.h"

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
void	ft_hashtable_pretty_print(t_hashtable *ht)
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
