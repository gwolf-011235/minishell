/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:38 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 16:00:24 by gwolf            ###   ########.fr       */
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
 * The hashtable has an elements array, which are all linked lists.
 * The function has to loop trhough the whole array.
 * And per array it has to loop through the linked list.
 * This function only copies the pointers in the hashtable.
 * Only variables which have a value are copied.
 * @param ht Environment table which to copy.
 * @param envp Where to save pointers.
 * @return t_err SUCCESS
 */
t_err	ft_envp_fill(t_hashtable *ht, char **envp, bool all)
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
				if (tmp->export && (all || tmp->has_value))
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
 * @brief Create a NULL-terminated environment pointer (envp)
 *
 * Malloc char array of num_values of hashtable plus 1 for terminator.
 * Fetch all elements with ft_envp_fill() with switch set to false.
 * Handles errors.
 * @param ht Environment from which to copy.
 * @param envp Pointer to char**, where to save.
 */
void	ft_envp_create(t_hashtable *ht, char ***envp)
{
	size_t	size;

	size = ht->num_values - (ht->num_elements - ht->num_exports) + 1;
	*envp = NULL;
	if (ft_err_malloc((void **)envp, sizeof(char *) * size, "minishell: malloc")
		== ERR_MALLOC)
	{
		ft_putendl_fd("minishell: warning: could not create environment.", 2);
		return ;
	}
	ft_envp_fill(ht, *envp, false);
}

/**
 * @brief Create envp of all elements
 *
 * See also ft_envp_create().
 * Difference: includes all elements of hashtable.
 * Malloc char array of num_elements of hashtable plus 1 for terminator.
 * Fetch all elements with ft_envp_fill() with switch set to true.
 * @param ht Environment from which to copy.
 * @param envp Pointer to char**, where to save.
 * @return t_err ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_envp_create_all(t_hashtable *ht, char ***envp)
{
	if (!ht || !envp)
		return (ERR_EMPTY);
	*envp = malloc(sizeof(char *) * (ht->num_exports + 1));
	if (!*envp)
		return (ERR_MALLOC);
	ft_envp_fill(ht, *envp, true);
	return (SUCCESS);
}

/**
 * @brief Destroy envp.
 *
 * Check if envp exists. If yes:
 * Free the envp and set to NULL.
 * Does not free elements.
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
