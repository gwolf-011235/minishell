/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_h.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/01 12:06:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a standard string if replacement wasn't found.
 *
 * Strdup the macro UNKNOWN defined in minishell.h and save it.
 *
 * @param replacement Pointer pointer where to save string.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_not_found(char **replacement)
{
	if (!replacement)
		return (ERR_EMPTY);
	*replacement = strdup(UNKNOWN);
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Create and save hostname string from provided string
 *
 * This function expects a value of env_var SESSION_MANAGER.
 * Search for "local/" and add 6 to get start of hostname.
 * Search for '.' or ':' to get end, if not found ft_strlen is used.
 * Create a substring.
 *
 * @param replacement Pointer pointer where to save string.
 * @param str The value of SESSION_MANAGER.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_create_hostname(char **replacement, const char *str)
{
	char	*start;
	char	*end;

	if (!replacement || !str)
		return (ERR_EMPTY);
	start = ft_strnstr(str, "local/", ft_strlen(str)) + 6;
	end = ft_strchr(start, '.');
	if (!end)
		end = ft_strchr(start, ':');
	if (!end)
		end = start + ft_strlen(start) - 1;
	*replacement = ft_substr(start, 0, end - start);
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Creates replacement string for prompt \h
 *
 * Search for env_var SESSION_MANAGER.
 * If found search for "local/" after where localhost name is saved.
 * Create string with sub function.
 * If any not found create UNKNOWN with sub function.
 *
 * @param replacement Pointer pointer where to save string.
 * @param sym_tab Symbol table where to search for env_var.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_h(char **replacement, t_hashtable sym_tab)
{
	t_error		err;
	t_env_var	env_var;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	env_var = ft_hashtable_lookup(sym_tab, "SESSION_MANAGER");
	if (!env_var || !ft_strnstr(env_var->value, "local/",
			ft_strlen(env_var->value)))
		err = ft_prompt_replace_not_found(replacement);
	else
		err = ft_prompt_create_hostname(replacement, env_var->value);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
