/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_w.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/01 13:14:21 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Tries to replace env_var $HOME in string with tilde.
 *
 * Search for $HOME. If found ft_strncmp with string: it should only replace
 * if string starts with $HOME.
 * Replace the token $HOME with '~' with ft_replace_token().
 * Also returns SUCCESS if $HOME not found or ft_strncmp not zero - no error.
 *
 * @param replacement Where to replace $HOME with tilde.
 * @param sym_tab Environment.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_tilde(char **replacement, t_hashtable sym_tab)
{
	t_error		err;
	t_env_var	env_var;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(sym_tab, "HOME");
	if (!env_var || !env_var->value)
		return (SUCCESS);
	if (ft_strncmp(env_var->value, *replacement,
			ft_strlen(env_var->value)))
		return (SUCCESS);
	err = ft_replace_token(replacement, env_var->value, "~");
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Creates replacement string for prompt \w
 *
 * Search for env_var $PWD.
 * If found ft_strdup value and save in replacement.
 * If not found create UNKNOWN with ft_prompt_replace_not_found().
 * Try to replace $HOME with ft_prompt_replace_tilde().
 *
 * @param replacement Pointer pointer where to save string.
 * @param sym_tab Symbol table where to search for env_var.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_w(char **replacement, t_hashtable sym_tab)
{
	t_error		err;
	t_env_var	env_var;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(sym_tab, "PWD");
	if (!env_var || !env_var->value)
	{
		err = ft_prompt_replace_not_found(replacement);
		if (err != SUCCESS)
			return (err);
		return (SUCCESS);
	}
	*replacement = ft_strdup(env_var->value);
	if (!*replacement)
		return (ERR_MALLOC);
	err = ft_prompt_replace_tilde(replacement, sym_tab);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
