/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:17:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 23:57:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hashtable_utils.c
 * @brief Utils functions to use with env hashtable
 */

#include "hashtable.h"

/**
 * @brief Generate index in hashtable of given string via hashfunction.
 *
 * It uses the hashfunction of the passed hashtable to create the hash.
 * With % size the hash is made to fit the hashtable as index.
 * @param ht Used hashtable
 * @param key String to check the hash for
 * @param keylen Length of the given string
 * @return size_t Index of the given string
 */
size_t	ft_hashtable_index(t_hashtable *ht, const char *key, size_t keylen)
{
	size_t	result;

	result = ht->hash(key, keylen) % ht->size;
	return (result);
}

/**
 * @brief Search for env_var in hashtable.
 *
 * Check if params are empty.
 * Generate index of given env_var and loop through list.
 * If element is found return the element.
 * @param ht Hashtable in which to look
 * @param string env_string which should be looked up
 * @param keylen Length of env_var (everything before =)
 * @return t_env_var* element if found, NULL if not.
 */
t_env_var	*ft_hashtable_lookup(
	t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;

	if (ht == NULL || string == NULL || keylen == 0)
		return (NULL);
	index = ft_hashtable_index(ht, string, keylen);
	tmp = ht->elements[index];
	while (tmp != NULL && (tmp->keylen != keylen
			|| (ft_strncmp(tmp->env_string, string, tmp->keylen) != 0)))
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

/**
 * @brief Increase or decrease element numbers in hashtable.
 *
 * @param ht Hashtable which gets updated.
 * @param tmp Inserted / deleted element
 * @param num Value to add to element numbers (neagtive to decrease).
 */
void	ft_hashtable_vary_nums(t_hashtable *ht, t_env_var *tmp, int num)
{
	ht->num_elements += num;
	if (tmp->export)
		ht->num_exports += num;
	if (tmp->has_value)
		ht->num_values += num;
}
