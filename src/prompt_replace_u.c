/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 14:57:43 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prompt_replace_u.c
 * @brief Create replacement for token u = USER
 */
#include "mod_prompt.h"

/**
 * @brief Creates replacement string for token \u.
 *
 * Search for env_var $USER.
 * If found ft_strdup value and save in replacement.
 * If not found create UNKNOWN with sub function.
 *
 * @param replacement Pointer pointer where to save string.
 * @param sym_tab Symbol table where to search for env_var.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_err	ft_replace_u(char **replacement, t_hashtable *sym_tab)
{
	t_err		err;
	t_env_var	*env_var;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(sym_tab, "USER", 4);
	if (!env_var || !env_var->value)
	{
		err = ft_replace_not_found(replacement);
		if (err != SUCCESS)
			return (err);
		return (SUCCESS);
	}
	*replacement = ft_strdup(env_var->value);
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}
