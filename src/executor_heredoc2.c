/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:20:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 16:10:02 by sqiu             ###   ########.fr       */
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
t_err	ft_initiate_heredoc(int index, char **name, int *fd)
{
	t_err	err;

	err = ft_name_heredoc(index, name);
	if (err == ERR_MALLOC)
		return (err);
	*fd = open(*name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
		return (ERR_OPEN);
	return (SUCCESS);
}
