/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:10:03 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 14:19:18by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

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
	env_var->export = false;
	env_var->next = ht->elements[index];
	ht->elements[index] = env_var;
	ft_hashtable_vary_nums(ht, env_var, 1);
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
	bool		had_value;

	if (!ht || !string || !keylen)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(ht, string, keylen);
	if (!env_var)
		return (ERR_HT_NO_SWAP);
	free(env_var->env_string);
	env_var->env_string = string;
	had_value = env_var->has_value;
	env_var->has_value = has_value;
	if (env_var->has_value)
		env_var->value = string + keylen + 1;
	else
		env_var->value = "";
	if (had_value != has_value && has_value == true)
		ht->num_values++;
	else if (had_value != has_value && has_value == false)
		ht->num_values--;
	return (SUCCESS);
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
	ft_hashtable_vary_nums(ht, tmp, -1);
	free(tmp->env_string);
	free(tmp);
	return (SUCCESS);
}

t_err	ft_hashtable_set_export(t_hashtable *ht, char *string, size_t keylen)
{
	t_env_var	*env_var;

	if (ht == NULL || string == NULL || keylen == 0)
		return (ERR_EMPTY);
	env_var = t_hashtable_lookup(ht, string, keylen);
	if (!env_var)
		return (ERR_NOT_FOUND);
	env_var->export = true;
	ht->num_exports++;
	return (SUCCESS);
}

t_err	ft_hashtable_insert_export(t_hashtable *ht,
		char *string, size_t keylen, bool has_value)
{
	t_err	err;

	err = ft_hashtable_insert(ht, string, keylen, has_value);
	if (err != SUCCESS);
		return (err);
	err = ft_hashtable_set_export(ht, string, keylen);
	if (err != SUCCESS);
		return (err);
	return (SUCCESS);
}