/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:17:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 18:01:26 by gwolf            ###   ########.fr       */
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
 * @brief Insert an env-string into hashtable.
 *
 * Check if any param is empty and if key is already inserted.
 * Generate index and malloc new element.
 * Set new element as head of the list pointed to by index.
 * @param ht Hashtable in which to insert
 * @param string env_string which should be inserted
 * @param keylen Length of env_var (everything before =)
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC, ERR_HT_NO_INSERT
 */
t_err	ft_hashtable_insert(t_hashtable *ht,
		char *string, size_t keylen, bool has_value)
{
	size_t		index;
	t_env_var	*env_var;

	if (ht == NULL || string == NULL || keylen == 0)
		return (ERR_EMPTY);
	if (ft_hashtable_lookup(ht, string, keylen) != NULL)
		return (ERR_HT_NO_INSERT);
	index = ft_hashtable_index(ht, string, keylen);
	env_var = malloc(sizeof(*env_var));
	if (!env_var)
		return (ERR_MALLOC);
	env_var->env_string = string;
	env_var->keylen = keylen;
	env_var->has_value = has_value;
	if (env_var->has_value)
		env_var->value = string + keylen + 1;
	else
		env_var->value = "";
	env_var->next = ht->elements[index];
	ht->elements[index] = env_var;
	ht->num_elements++;
	return (SUCCESS);
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
 * @brief Delete one element of hashtable.
 *
 * Check if params are empty.
 * Generate index and set tmp pointer to start of list.
 * Set prev pointer to NULL.
 * Loop through the list and update tmp and prev pointers.
 * If tmp == NULL no element was found.
 * If prev == NULL element is at start of list.
 * If element is found free.
 * Then free element and update next pointer.
 * @param ht Hashtable in which to delete one element
 * @param string env_string which should be deleted
 * @param keylen length of env_var (everthing before =)
 * @return t_err SUCCESS, ERR_EMPTY, ERR_HT_NO_DELETE
 */
t_err	ft_hashtable_delete(
	t_hashtable *ht, char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;
	t_env_var	*prev;

	if (ht == NULL || string == NULL || keylen == 0)
		return (ERR_EMPTY);
	index = ft_hashtable_index(ht, string, keylen);
	tmp = ht->elements[index];
	prev = NULL;
	while (tmp != NULL && (tmp->keylen != keylen
			|| (ft_strncmp(tmp->env_string, string, tmp->keylen) != 0)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (ERR_HT_NO_DELETE);
	if (prev == NULL)
		ht->elements[index] = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->env_string);
	free(tmp);
	ht->num_elements--;
	return (SUCCESS);
}

/**
 * @brief Swap an env_string in hashtable
 *
 * Search for key of given string, if not found return.
 * Free the old env_str.
 * Set the passed string and adjust value.
 * @param ht Hashtable where to insert.
 * @param string Env_string which should be inserted
 * @param keylen Length of the key.
 * @return t_err ERR_EMPTY, ERR_HT_NO_SWAP, SUCCESS
 */
t_err	ft_hashtable_swap(t_hashtable *ht,
		char *string, size_t keylen, bool has_value)
{
	t_env_var	*env_var;

	if (!ht || !string || !keylen)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(ht, string, keylen);
	if (!env_var)
		return (ERR_HT_NO_SWAP);
	free(env_var->env_string);
	env_var->env_string = string;
	env_var->has_value = has_value;
	if (env_var->has_value)
		env_var->value = string + keylen + 1;
	else
		env_var->value = "";
	return (SUCCESS);
}
