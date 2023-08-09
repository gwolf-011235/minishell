/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_h.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/09 19:20:03 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file prompt_replace_h.c
 * @brief Create replacement for token h = hostname.
 */
#include "mod_prompt.h"

/**
 * @brief Retrieve hostname and save in provided pointer.
 *
 * The current hostname is saved in /proc/sys/kernel/hostname.
 * Open this file and retrieve hostname via get_next_line().
 * Hostname is delimited by newline. Search for '\n' and replace with '\0'
 * @param replacement Pointer pointer where to save string.
 * @return t_err SUCCESS, ERR_OPEN, ERR_MALLOC
 */
t_err	ft_retrieve_hostname(char **replacement)
{
	int		fd;
	char	*newline;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	if (fd == -1)
		return (ERR_OPEN);
	*replacement = get_next_line(fd);
	if (!*replacement)
		return (ERR_MALLOC);
	newline = ft_strrchr(*replacement, '\n');
	if (newline)
		*newline = '\0';
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Creates replacement string for token \h.
 *
 * Search for env_var $SESSION_MANAGER.
 * If found search for "local/" after where localhost name is saved.
 * Create string with sub function.
 * If any not found create UNKNOWN with sub function.
 *
 * @param replacement Pointer pointer where to save string.
 * @param sym_tab Symbol table where to search for env_var.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_err	ft_replace_h(char **replacement, t_hashtable *sym_tab)
{
	t_err		err;

	if (!replacement || !sym_tab)
		return (ERR_EMPTY);
	err = ft_retrieve_hostname(replacement);
	if (err == ERR_MALLOC)
		return (err);
	else if (err != SUCCESS)
		err = ft_replace_not_found(replacement);
	return (err);
}
