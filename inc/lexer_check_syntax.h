/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_syntax.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:45:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/24 11:31:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_CHECK_SYNTAX_H
# define LEXER_CHECK_SYNTAX_H

# include <stddef.h>

# include "libft.h"

# include "minishell_error.h"
# include "utils.h"

# define SYNTAX_QUOTE "minishell: syntax error after unclosed quotes: %c\n"
# define SYNTAX_TOKEN "minishell: syntax error near unexpected token `%c'\n"
# define SYNTAX_NL "minishell: syntax error near unexpected token `newline'\n"

t_error	ft_check_syntax(const char *input);

#endif