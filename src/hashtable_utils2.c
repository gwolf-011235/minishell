/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:39 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/07 11:22:49 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_error	ft_hashtable_swap(t_hashtable *ht, char *string, size_t keylen)
{
	t_env_var	*env_var;

	if (!ht || !string || !keylen)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(ht, string, keylen);
	if (!env_var)
		return (ERR_HT_NO_SWAP);
	free(env_var->env_string);
	env_var->env_string = string;
	env_var->value = string + keylen + 1;
	return (SUCCESS);
}
