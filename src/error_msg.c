/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:40:16 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 18:03:34 by sqiu             ###   ########.fr       */
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
		ft_print_warning_message(trigger, ": Is a directory");
		return (ERR_DIR);
	}
	else if (err == ERR_HEREDOC_OPEN)
	{
		g_status = 1;
		ft_print_warning_message(trigger, ": could not create heredoc");
		return (ERR_HEREDOC_OPEN);
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
		ft_print_warning_message(trigger, ": No such file or directory");
		return (ERR_NO_DIR);
	}
	else if (err == ERR_UNKNOWN_CMD)
	{
		g_status = 127;
		ft_print_warning_message(trigger, ": command not found");
		return (ERR_UNKNOWN_CMD);
	}
	else if (err == ERR_PERM_DENIED)
	{
		g_status = 126;
		ft_print_warning_message(trigger, ": Permission denied");
		return (ERR_PERM_DENIED);
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
		ft_print_warning_message(trigger, ": ambiguous redirect");
		return (ERR_AMBIGUOUS);
	}
	return (SUCCESS);
}

/**
 * @brief Prints the warning message.
 * 
 * @param trigger 	Trigger causing the warning.
 * @param msg 		Individual message according to warning.
 */
void	ft_print_warning_message(char *trigger, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(trigger, 2);
	ft_putendl_fd(msg, 2);
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
