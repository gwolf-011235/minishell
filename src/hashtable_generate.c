/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_generate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/19 11:22:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"

uint64_t	ft_hash_fnv1(const char *string, size_t len)
{
	uint64_t	hash_value;
	size_t		i;

	hash_value = FNV_OFFSET;
	i = 0;
	while (i < len)
	{
		hash_value *= FNV_PRIME;
		hash_value ^= string[i];
		i++;
	}
	return (hash_value);
}

t_hashtable	*ft_hashtable_create(uint32_t size, t_hashfunction *hf)
{
	t_hashtable	*ht;

	ht = malloc(sizeof(*ht));
	if (!ht)
		return (NULL);
	ht->size = size;
	ht->hash = hf;
	ht->elements = ft_calloc(sizeof(t_env_var *), ht->size);
	return (ht);
}

void	ft_hashtable_destroy(t_hashtable *ht)
{
	uint32_t	i;
	t_env_var	*tmp;

	i = 0;
	while (i < ht->size)
	{
		while (ht->elements[i] != NULL)
		{
			tmp = ht->elements[i];
			ht->elements[i] = ht->elements[i]->next;
			free((void *)(tmp->env_string));
			free(tmp);
		}
		i++;
	}
	free(ht->elements);
	free(ht);
}
