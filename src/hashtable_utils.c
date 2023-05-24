/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:17:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 12:42:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generate index in hashtable of given string via hashfunction
 * It uses the hashfunction of the passed hashtable to create the hash.
 * With % size the hash is made to fit the hashtable as index.
 * Static since no where else planned to use.
 * @param ht Used hashtable
 * @param key String to check the hash for
 * @param keylen Length of the given string
 * @return size_t Index of the given string
 */
static size_t	ft_hashtable_index(
	t_hashtable *ht, const char *key, size_t keylen)
{
	size_t	result;

	result = ht->hash(key, keylen) % ht->size;
	return (result);
}

/**
 * @brief Insert an env-string into hashtable
 * Check if any param is empty and if key is already inserted.
 * Generate index and malloc new element.
 * Set new element as head of the list pointed to by index.
 * @param ht Hashtable in which to insert
 * @param string env_string which should be inserted
 * @param keylen Length of env_var (everything before =)
 * @return t_error SUCCESS if element inserted
 */
t_error	ft_hashtable_insert(t_hashtable *ht, const char *string, size_t keylen)
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
	env_var->value = string + keylen + 1;
	env_var->next = ht->elements[index];
	ht->elements[index] = env_var;
	return (SUCCESS);
}

/**
 * @brief Search for env_var in hashtable
 * Check if params are empty.
 * Generate index of given env_var and loop through list
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
 * @brief Delete one element of hashtable
 * Check if any param is NULL
 * Generate index and set tmp pointer to start of list.
 * Set prev pointer to NULL.
 * Loop through the list and update tmp and prev pointers.
 * If tmp == NULL no element was found.
 * If prev == NULL element is at start of list.
 * If element is found free string and element. Also update next pointer.
 * @param ht Hashtable in which to delete one element
 * @param string env_string which should be deleted
 * @param keylen length of env_var (everthing before =)
 * @return t_error SUCCESS if deleted.
 */
t_error	ft_hashtable_delete(
	t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;
	t_env_var	*prev;
	const char	*env_string;

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
	return (SUCCESS);
}

/**
 * @brief Print out all elements
 * Prints a start table. Then prints all elements it finds at the indexes.
 * If more then one element is at a given index they get separated by newline.
 * Can be adapted to just print env_vars.
 * @param ht Hashtable to print.
 */
void	ft_hashtable_print(t_hashtable *ht)
{
	uint32_t	i;
	t_env_var	*tmp;

	printf("Start Table\n");
	i = 0;
	while (i < ht->size)
	{
		if (ht->elements[i] == NULL)
			printf("\t%i\t---\n", i);
		else
		{
			printf("\t%i\t\n", i);
			tmp = ht->elements[i];
			while (tmp != NULL)
			{
				printf("%s\n", tmp->env_string);
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
	printf("End Table\n");
}
