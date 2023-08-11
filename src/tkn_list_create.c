/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_list_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:43:24 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 22:05:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tkn_list_create.c
 * @brief Create new nodes.
 */
#include "tkn_list.h"

/**
 * @brief Create a new node and add it to the end of the token list.
 *
 * @param lst_head	Head node of token list.
 * @param content	Content string to be written into new node.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_new_node(t_tkn_list	**lst_head, char *content)
{
	t_tkn_list	*new;

	new = malloc(sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->type = ARG;
	new->next = NULL;
	new->prev = NULL;
	ft_add_lst(lst_head, new);
	return (SUCCESS);
}

/**
 * @brief Go to end of token list and connect given token.
 *
 * If there is a (last) node in the list, connect new token to the end.
 * If the list is yet empty, set new token as head of the list.
 * @param lst Token list.
 * @param new Given token to be added to token list.
 */
void	ft_add_lst(t_tkn_list **lst, t_tkn_list *new)
{
	t_tkn_list	*tmp;

	tmp = ft_last(*lst);
	if (tmp)
	{
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}

/**
 * @brief Create new node, insert after current node, move pointer.
 *
 * @param cur_node Pointer to current node.
 * @param content Content string.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_new_node_mid(t_tkn_list **cur_node, char *content)
{
	t_tkn_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->type = ARG;
	new->next = NULL;
	new->prev = NULL;
	ft_add_lst_mid(*cur_node, new);
	(*cur_node) = (*cur_node)->next;
	return (SUCCESS);
}

/**
 * @brief Insert new node in the list.
 *
 * New node is next of current node.
 * If there is next node of current node, update pointer to new.
 * @param cur Pointer to current node.
 * @param new Pointer to newly created node.
 */
void	ft_add_lst_mid(t_tkn_list *cur, t_tkn_list *new)
{
	new->next = cur->next;
	if (cur->next)
		cur->next->prev = new;
	cur->next = new;
	new->prev = cur;
}
