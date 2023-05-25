/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_generate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 22:02:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hashtable_generate.c
 * @brief Contains functions to create and destroy hashtable.
 */

#include "hashtable.h"
#include "libft.h"

/**
 * @brief Implements the FNV (Fowler-Noll-Vo)-1 hash function.
 *
 * FNV_OFFSET and FNV_PRIME are defined in hashtable.h
 * @param string The string to generate a hash from
 * @param len Length of the string
 * @return uint64_t Hash value of string
 */
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

/**
 * @brief Creates and initializes a new t_hashtable.
 *
 * Mallocs the struct, then sets size to param size and hashfunction to
 * param hf. Then enough pointers get calloc'd to fit size. If malloc of
 * hashtable or calloc of elements fail NULL gets returned.
 * @param size Size of hashtable - that many elements pointer get alloc'd
 * @param hf Pointer to hashfunction which should be used
 * @return t_hashtable* pointer to malloc'd hashtable; NULL if malloc fail
 */
t_hashtable	*ft_hashtable_create(uint32_t size, t_hashfunction *hf)
{
	t_hashtable	*ht;

	ht = malloc(sizeof(*ht));
	if (!ht)
		return (NULL);
	ht->size = size;
	ht->hash = hf;
	ht->elements = ft_calloc(sizeof(t_env_var *), ht->size);
	if (!ht->elements)
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

/**
 * @brief Deallocate given hashtable.
 *
 * Loop through all elements in elements pointer.
 * Free the string and the element.
 * At the end free elements pointer and hashtable.
 * @param ht Hashtable to destroy
 */
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
