/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:20:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/13 23:52:57 by sqiu             ###   ########.fr       */
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

/**
 * @brief Print warning message when EOF is
 * encountered while heredoc is reading from STDIN.
 *
 * Print prompt2.
 * Then print the warning message with
 * expected the delimiter.
 * @param delim		Delimiter string of heredoc.
 * @return t_err	ERR_HEREDOC_QUIT
 */
t_err	ft_print_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document at line 42 \
delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
	return (ERR_HEREDOC_QUIT);
}
