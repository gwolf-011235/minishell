/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_syntax.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:45:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/17 10:47:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_SYNTAX_H
# define MOD_SYNTAX_H

# include <stddef.h>

# include "libft.h"
# include "minishell_error.h"
# include "minishell_utils.h"

# define SYNTAX_QUOTE "minishell: syntax error after unclosed quotes: %c\n"
# define SYNTAX_TOKEN "minishell: syntax error near unexpected token `%c'\n"
# define SYNTAX_NL "minishell: syntax error near unexpected token `newline'\n"

t_err	ft_check_syntax(const char *input);
t_err	ft_check_redirect(const char *input, size_t pos, char symbol);
t_err	ft_check_pipe(const char *input, size_t pos);
t_err	ft_quote_skipper(const char *quote_start, size_t *i, char target);

#endif