/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:40:16 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 19:00:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "libft.h"
#include <unistd.h>
#include "mod_executor.h"

/**
 * @brief Print warning messages depending on
 * received indicator and trigger string.
 *
 * @param indic		Indicator string for error message.
 * @param trigger	Trigger string causing the error.
 * @return t_err	ERR_HEREDOC_EOF, ERR_DIR, SUCCESS
 */
t_err	ft_print_warning(char *indic, char *trigger)
{
	if (!ft_strncmp(indic, "heredoc", 8))
	{
		ft_putstr_fd("minishell: warning: here-document at line 42 \
	delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd("')", 2);
		return (ERR_HEREDOC_EOF);
	}
	else if (!ft_strncmp(indic, "dir", 4))
	{
		g_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (ERR_DIR);
	}
	else
		return (ft_print_warning2(indic, trigger));
}

/**
 * @brief Continuation of ft_print_warning()
 *
 * @param indic 	Indicator string for error message.
 * @param trigger 	Trigger string causing the error.
 * @return t_err 	ERR_NO_DIR, SUCCESS
 */
t_err	ft_print_warning2(char *indic, char *trigger)
{
	if (!ft_strncmp(indic, "nodir", 6))
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (ERR_NO_DIR);
	}
	if (!ft_strncmp(indic, "nocmd", 6))
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": command not found", 2);
		return (SUCCESS);
	}
	if (!ft_strncmp(indic, "ambiguous", 10))
	{
		g_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (SUCCESS);
	}
	return (SUCCESS);
}

/**
 * @brief Prints error message depending on passed error code.
 *
 * @param err Passed error code.
 * @return Passed error code.
 */
t_err	ft_print_error(t_err err)
{
	if (err == ERR_LEXER)
		ft_putendl_fd("minishell: error: lexer has the sad", 2);
	else if (err == ERR_EXPANDER)
		ft_putendl_fd("minishell: error: expander has the sad", 2);
	return (err);
}
