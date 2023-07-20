/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:01:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/20 09:04:46 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_EXPAND_H
# define LEXER_EXPAND_H

# include "minishell_error.h"
# include "minishell.h"

//expand_expr.c
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);

#endif