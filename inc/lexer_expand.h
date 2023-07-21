/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:01:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/20 09:16:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_EXPAND_H
# define LEXER_EXPAND_H

# include "minishell_error.h"
# include "minishell.h"

//import from expand_expr.c
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);

t_error	ft_expand_tkn_lst(t_tkn_list *list, t_data *data);

#endif