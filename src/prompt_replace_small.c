/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_small.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:05:43 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/02 17:54:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create string if some $var for replacement wasn't found.
 *
 * Use ft_strdup() on macro UNKNOWN defined in minishell.h and save it.
 *
 * @param replacement Pointer pointer where to save string.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_not_found(char **replacement)
{
	if (!replacement)
		return (ERR_EMPTY);
	*replacement = ft_strdup(UNKNOWN);
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Creates replacement string for token \n.
 *
 * Just simply ft_strdup() '\n' and saves it.
 * Sym_tab is voided to use this ft in ft pointer.
 *
 * @param replacement Where to save string.
 * @param sym_tab symbol_table - not used.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_n(char **replacement, t_hashtable *sym_tab)
{
	t_error		err;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	(void)sym_tab;
	*replacement = ft_strdup("\n");
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Creates replacement string for token \r.
 *
 * Just simply ft_strdup() '\r' and saves it.
 * Sym_tab is voided to use this ft in ft pointer.
 *
 * @param replacement Where to save string.
 * @param sym_tab symbol_table - not used.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_r(char **replacement, t_hashtable *sym_tab)
{
	t_error		err;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	(void)sym_tab;
	*replacement = ft_strdup("\r");
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Creates empty string for wrong token.
 *
 * Just simply ft_strdup() "" (empty string) and saves it.
 * Sym_tab is voided to use this ft in ft pointer.
 *
 * @param replacement Where to save string.
 * @param sym_tab symbol_table - not used.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_prompt_replace_empty(char **replacement, t_hashtable *sym_tab)
{
	t_error		err;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	(void)sym_tab;
	*replacement = ft_strdup("");
	if (!*replacement)
		return (ERR_MALLOC);
	return (SUCCESS);
}
