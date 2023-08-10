/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:45:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 22:30:14 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKN_LIST_H
# define TKN_LIST_H

/* ====== Includes ====== */

# include <stddef.h>
# include <stdlib.h>
# include "minishell_error.h"

/* ====== Structs ====== */

/**
 * @brief Enum of different types that can be assigned to tokens
 *
 * @param ARG		Any string that is not connected to redirects, piping or newlines.
 * @param INFILE	Redirect evoking an infile.
 * @param HEREDOC	Redirect evoking a heredoc.
 * @param OUTFILE	Redirect evoking an outfile.
 * @param APPEND	Redirect evoking an outfile in append mode.
 * @param PIPE		Char indicating piping of commands.
 * @param Newline	Char indicating end of a command.
 */
typedef enum e_type
{
	ARG,
	ASSIGN,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
	NEW_LINE,
	AMBIGUOUS,
	DELETE
}	t_type;

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
	t_type				type;
	struct s_tkn_list	*prev;
	struct s_tkn_list	*next;
}	t_tkn_list;

/* ====== Functions ====== */

//create
t_err		ft_new_node(t_tkn_list	**lst_head, char *content);
void		ft_add_lst(t_tkn_list **lst, t_tkn_list *new);
t_err		ft_new_node_mid(t_tkn_list **lst_head, char *content);
void		ft_add_lst_mid(t_tkn_list *cur, t_tkn_list *new);

//search
t_tkn_list	*ft_list_first(t_tkn_list *list);
t_tkn_list	*ft_last(t_tkn_list *lst);

//delete
void		ft_del_node(t_tkn_list *lst);
void		ft_del_node_mid(t_tkn_list **lst_head);
void		ft_del_target_type(t_tkn_list **head, t_type target);
void		ft_del_prev_n(t_tkn_list *cur_node, size_t n);
void		ft_free_lst(t_tkn_list **lst);

#endif