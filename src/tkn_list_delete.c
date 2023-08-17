/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_list_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:43:35 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/16 08:25:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tkn_list_delete.c
 * @brief Deletion of nodes.
 */
#include "tkn_list.h"

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
 * Update pointers to that *cur_node->prev and *cur_node->next point to
 * the right node (if they exist).
 * Use ft_del_node() to delete the target node.
 * Move pointer forward.
 * @param cur_node Pointer pointer to current node.
 * @return t_err SUCCESS
 */
void	ft_del_node_mid(t_tkn_list **cur_node)
{
	t_tkn_list	*tmp;

	tmp = *cur_node;
	*cur_node = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	ft_del_node(tmp);
}

/**
 * @brief Deletes all nodes of specific type.
 *
 * If target node is at first place move the head forward.
 * If not iterate through list and del nodes with target type.
 * @param head Pointer to head of list.
 * @param target Type to delete.
 */
void	ft_del_target_type(t_tkn_list **head, t_type target)
{
	t_tkn_list	*tmp;

	while ((*head) && (*head)->type == target)
		ft_del_node_mid(head);
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == target)
			ft_del_node_mid(&tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

/**
 * @brief Iterates n nodes back and deletes found node.
 *
 * If position at nth pos is NULL do nothing
 * @param cur_node Pointer to current node.
 * @param n How many times to iterate back.
 * @return t_err SUCCESS
 */
void	ft_del_prev_n(t_tkn_list *cur_node, size_t n)
{
	size_t		i;

	i = 0;
	while (cur_node && i++ < n)
		cur_node = cur_node->prev;
	if (cur_node)
		ft_del_node_mid(&cur_node);
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
