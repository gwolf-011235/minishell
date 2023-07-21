/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:38 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 14:50:57 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_envp.c
 * @brief Create and destroy environment pointer.
 */
#include "mod_env.h"

/**
 * @brief Loop through all elements and copy the pointers.
 *
 * @param ht Environment table which to copy.
 * @param envp Where to save pointers.
 * @return t_err SUCCESS
 */
t_err	ft_envp_fill(t_hashtable *ht, char **envp)
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
 * @return t_err ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_envp_create(t_hashtable *ht, char ***envp)
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
 * Check if envp exists. If yes:
 * Free the envp and set to NULL.
 * Does not free elements.
 *
 * @param envp The pointer to free.
 * @return t_err SUCCESS
 */
t_err	ft_envp_destroy(char ***envp)
{
	if (*envp)
	{
		free(*envp);
		*envp = NULL;
	}
	return (SUCCESS);
}
