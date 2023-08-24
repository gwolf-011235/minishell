/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:20:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 15:46:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_heredoc2.c
 * @brief Functions to handle heredoc feature.
 */

#include "mod_executor.h"

/**
 * @brief Set heredoc name and open it.
 *
 * @param index 	Index of current cmd.
 * @param name 		Pointer to name of heredoc to be created.
 * @param fd 		File descriptor for heredoc.
 * @return t_err 	ERR_MALLOC, ERR_OPEN, SUCCESS
 */
t_err	ft_init_heredoc(t_hdoc *heredoc, int index, bool quoted, char *delim)
{
	t_err	err;

	err = ft_name_heredoc(index, &heredoc->name);
	if (err == ERR_MALLOC)
		return (err);
	heredoc->fd = open(heredoc->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc->fd == -1)
		return (ERR_OPEN);
	heredoc->delim = delim;
	heredoc->delim_len = ft_strlen(delim);
	heredoc->quoted = quoted;
	return (SUCCESS);
}
