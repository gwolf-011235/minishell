/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:49 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/12 21:28:22 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_LIST_H
# define LEXER_LIST_H

/* ====== Includes ====== */

//# include "minishell.h"
# include "lexer_src.h"
# include "lexer_tok.h"

/* ====== Definitions ====== */



/* ====== Functions ====== */

t_error	ft_list_token(t_data *data, char *input);
void	ft_init_lexer(t_src *src, char *input);
t_error	ft_new_node(t_data *data, char *content);
void	ft_free_lst(t_tkn_list **lst, void (*del)(void*));
void	ft_add_list(t_tkn_list **lst, t_tkn_list *new);

#endif