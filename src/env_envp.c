/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:38 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/07 12:01:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_envp.h"

/**
 * @brief Loop through all elements and copy the pointers.
 *
 * @param ht Environment table which to copy.
 * @param envp Where to save pointers.
 * @return t_error SUCCESS
 */
static t_error	ft_envp_fill(t_hashtable *ht, char **envp)
{
	uint32_t	i;
	t_env_var	*tmp;

	i = 0;
	while (i < ht->size)
	{
		if (ht->elements[i])
		{
			tmp = ht->elements[i];
			while (tmp != NULL)
			{
				*envp++ = tmp->env_string;
				tmp = tmp->next;
			}
		}
		i++;
	}
	*envp = NULL;
	return (SUCCESS);
}

/**
 * @brief Malloc a NULL-terminated envp
 *
 * Malloc num_elements of hashtable plus 1 for terminator.
 * Fetch all elements with ft_envp_fill().
 *
 * @param ht Environment from which to copy.
 * @param envp Pointer to char**, where to save.
 * @return t_error ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_error	ft_envp_create(t_hashtable *ht, char ***envp)
{
	if (!ht || !envp)
		return (ERR_EMPTY);
	*envp = malloc(sizeof(char *) * (ht->num_elements + 1));
	if (!*envp)
		return (ERR_MALLOC);
	ft_envp_fill(ht, *envp);
	return (SUCCESS);
}

/**
 * @brief Destroy envp.
 *
 * Free the envp and set to NULL.
 * Does not free elements.
 *
 * @param envp The pointer to free.
 * @return t_error SUCCESS
 */
t_error	ft_envp_destroy(char ***envp)
{
	free(*envp);
	*envp = NULL;
	return (SUCCESS);
}
