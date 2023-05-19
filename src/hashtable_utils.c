/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:17:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/19 11:24:53 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static size_t	ft_hashtable_index(
	t_hashtable *ht, const char *key, size_t keylen)
{
	size_t	result;

	result = ht->hash(key, keylen) % ht->size;
	return (result);
}

bool	ft_hashtable_insert(t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*env_var;

	if (ht == NULL || string == NULL || keylen == 0)
		return (false);
	//get rid of index since we get it from lookup?
	index = ft_hashtable_index(ht, string, keylen);
	//check if key is already inserted
	if (ft_hashtable_lookup(ht, string, keylen) != NULL)
		return (false);
	env_var = malloc(sizeof(*env_var));
	if (!env_var)
		return (false);
	env_var->env_string = string;
	env_var->keylen = keylen;
	env_var->value = string + keylen + 1;
	env_var->next = ht->elements[index];
	ht->elements[index] = env_var;
	return (true);
}

t_env_var	*ft_hashtable_lookup(
	t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;

	if (ht == NULL || string == NULL || keylen == 0)
		return (false);
	index = ft_hashtable_index(ht, string, keylen);
	tmp = ht->elements[index];
	while (tmp != NULL && (tmp->keylen != keylen
			|| (ft_strncmp(tmp->env_string, string, tmp->keylen) != 0)))
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

const char	*ft_hashtable_delete(
	t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;
	t_env_var	*prev;
	const char	*env_string;

	if (ht == NULL || string == NULL || keylen == 0)
		return (false);
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
		return (NULL);
	if (prev == NULL)
		ht->elements[index] = tmp->next;
	else
		prev->next = tmp->next;
	env_string = tmp->env_string;
	free(tmp);
	return (env_string);
}

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
