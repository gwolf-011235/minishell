/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:20:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 13:59:14 by gwolf            ###   ########.fr       */
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
 * @return t_err 	ERR_MALLOC, ERR_HEREDOC_OPEN, SUCCESS
 */
t_err	ft_init_heredoc(t_hdoc *heredoc, t_cmd *cmd, int curr_delim)
{
	if (ft_name_heredoc(cmd->index, &heredoc->name) == ERR_MALLOC)
		return (ERR_MALLOC);
	heredoc->fd = open(heredoc->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc->fd == -1)
	{
		cmd->execute = false;
		return (ft_print_warning(ERR_HEREDOC_OPEN, heredoc->name));
	}
	heredoc->delim = cmd->delims[curr_delim];
	heredoc->delim_len = ft_strlen(cmd->delims[curr_delim]);
	heredoc->quoted = cmd->hdoc_quoted[curr_delim];
	return (SUCCESS);
}
