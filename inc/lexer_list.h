/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:49 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 20:20:27 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_LIST_H
# define LEXER_LIST_H

/* ====== Includes ====== */

# include "minishell.h"
# include "lexer_src.h"
# include "lexer_tok.h"

/* ====== Definitions ====== */

typedef struct s_tkn_list
{
	char				*tkn_str;
	struct s_tkn_list	*prev;
	struct s_tkn_list	*next;
}	t_tkn_list;

/* ====== Functions ====== */


t_error	ft_new_node(t_tkn_list *new, t_tkn_list **prev, char *s);

#endif