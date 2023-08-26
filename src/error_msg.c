/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:40:16 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 17:30:48 by gwolf            ###   ########.fr       */
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
 * @param err		Indicator t_err for error message.
 * @param trigger	Trigger string causing the error.
 * @return t_err	ERR_HEREDOC_EOF, ERR_DIR, SUCCESS
 */
t_err	ft_print_warning(t_err err, char *trigger)
{
	if (err == ERR_HEREDOC_EOF)
	{
		ft_putstr_fd("minishell: warning: here-document at line 42 \
	delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd("')", 2);
		return (ERR_HEREDOC_EOF);
	}
	else if (err == ERR_DIR)
	{
		g_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (ERR_DIR);
	}
	else
		return (ft_print_warning2(err, trigger));
}

/**
 * @brief Continuation of ft_print_warning()
 *
 * @param indic 	Indicator string for error message.
 * @param trigger 	Trigger string causing the error.
 * @return t_err 	ERR_NO_DIR, SUCCESS
 */
t_err	ft_print_warning2(t_err err, char *trigger)
{
	if (err == ERR_NO_DIR)
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (ERR_NO_DIR);
	}
	else if (err == ERR_UNKNOWN_CMD)
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": command not found", 2);
		return (ERR_UNKNOWN_CMD);
	}
	else
		return (ft_print_warning3(err, trigger));
}

/**
 * @brief Continuation of ft_print_warning()
 *
 * @param indic 	Indicator string for error message.
 * @param trigger 	Trigger string causing the error.
 * @return t_err 	SUCCESS
 */
t_err	ft_print_warning3(t_err err, char *trigger)
{
	if (err == ERR_AMBIGUOUS)
	{
		g_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (ERR_AMBIGUOUS);
	}
	else if (err == ERR_HEREDOC_OPEN)
	{
		g_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": could not create heredoc", 2);
		return (ERR_HEREDOC_OPEN);
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
	else if (err == ERR_PARSER)
		ft_putendl_fd("minishell: error: parser has the sad", 2);
	else if (err == ERR_EXECUTOR)
		ft_putendl_fd("minishell: error: executor has the sad", 2);
	return (err);
}
