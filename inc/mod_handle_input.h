/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handle_input.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:47 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 15:18:19 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_HANDLE_INPUT_H
# define MOD_HANDLE_INPUT_H

/* ====== Includes ====== */

# include "minishell_error.h"
# include "minishell_struct.h"
# include "libft.h"

/* ====== Structs ====== */

/**
 * @brief List of token.
 *
 * Double-linked list of nodes that contain individual token strings. Each
 * node is connected to the previous and next node. The first node refers to
 * NUll as prev. The last node refers to NULL as next node.
 * @param content String containing token.
 */
typedef struct s_tkn_list
{
	char				*content;
	struct s_tkn_list	*prev;
	struct s_tkn_list	*next;
}	t_tkn_list;

/* ====== Functions ====== */

t_err	ft_lex_input(t_tkn_list	**lst_head, char *input);
void	ft_free_lst(t_tkn_list **lst);

#endif