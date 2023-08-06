/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_tkn_list2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:55:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 13:21:13by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_input_tkn_list2.c
 * @brief Deletion of nodes.
 */
#include "mod_handle_input.h"


/**
 * @brief Delete the content and the node itself.
 *
 * @param lst List containing the nodes to be deleted.
 * @param del Pointer to function to delete content of nodes.
 */
void	ft_del_node(t_tkn_list *lst)
{
	if (!lst)
		return ;
	free(lst -> content);
	free(lst);
}

/**
 * @brief Delete a node and move pointer forward.
 *
 * Update pointers to that *head->prev and *head->next point to
 * the right node (if they exist).
 * Use ft_del_node() to delete the old node.
 * Move the head pointer forward to *head->next.
 *
 * @param head Pointer pointer to current node.
 * @return t_err SUCCESS
 */
void	ft_del_node_mid(t_tkn_list **head)
{
	t_tkn_list	*cur;

	cur = *head;
	*head = cur->next;
	if (cur->next)
		cur->next->prev = cur->prev;
	if (cur->prev)
		cur->prev->next = cur->next;
	ft_del_node(cur);
}

/**
 * @brief Iterate through token list and free all nodes.
 *
 * @param lst Token list to be freed.
 */
void	ft_free_lst(t_tkn_list **lst)
{
	t_tkn_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		ft_del_node((*lst));
		*lst = tmp;
	}
	(*lst) = NULL;
}

/**
 * @brief Iterate to first node of given list.
 *
 * @param lst Pointer pointer to a list node.
 * @return t_err SUCCESS.
 */
t_tkn_list	*ft_list_first(t_tkn_list *list)
{
	while (list)
	{
		if (list->prev == NULL)
			break ;
		list = list->prev;
	}
	return (list);
}
