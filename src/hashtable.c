/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/17 18:15:33 by gwolf            ###   ########.fr       */
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

static size_t	ft_hashtable_index(t_hashtable *ht, const char *key, size_t keylen)
{
	size_t	result;

	result = ht->hash(key, keylen) % ht->size;
	return (result);
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
	//what to do about elements
	free(ht->elements);
	free(ht);
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
				printf("\"%s\" - ", tmp->env_string);
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
	printf("End Table\n");
}

bool	ft_hashtable_insert(t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*env_var;

	if (ht == NULL || string == NULL || keylen == 0)
		return (false);
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
	env_var->next =ht->elements[index];
	ht->elements[index] = env_var;
	return (true);
}

t_env_var	*ft_hashtable_lookup(t_hashtable *ht, const char *string, size_t keylen)
{
	size_t		index;
	t_env_var	*tmp;

	if (ht == NULL || string == NULL || keylen == 0)
		return (false);
	index = ft_hashtable_index(ht, string, keylen);
	tmp = ht->elements[index];
	while (tmp != NULL && tmp->keylen == keylen && (ft_strncmp(tmp->env_string, string, tmp->keylen) != 0))
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

const char	*ft_hashtable_delete(t_hashtable *ht, const char *string, size_t keylen)
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
	while (tmp != NULL && tmp->keylen == keylen && (ft_strncmp(tmp->env_string, string, tmp->keylen) != 0))
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
