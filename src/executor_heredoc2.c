/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:20:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 16:00:14 by gwolf            ###   ########.fr       */
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

/**
 * @brief Print warning message when EOF is
 * encountered while heredoc is reading from STDIN.
 *
 * Print prompt2.
 * Then print the warning message with
 * expected the delimiter.
 * @param delim		Delimiter string of heredoc.
 * @return t_err	ERR_HEREDOC_EOF
 */
t_err	ft_print_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document at line 42 \
delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
	return (ERR_HEREDOC_EOF);
}
