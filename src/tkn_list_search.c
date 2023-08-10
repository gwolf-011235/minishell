/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_list_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:43:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 22:07:01 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tkn_list_search.c
 * @brief Search for specific nodes.
 */
#include "tkn_list.h"

/**
 * @brief Iterate to first node of given list.
 *
 * @param lst Pointer pointer to a list node.
 * @return t_err SUCCESS.
 */
t_tkn_list	*ft_list_first(t_tkn_list *cur_node)
{
	while (cur_node)
	{
		if (cur_node->prev == NULL)
			break ;
		cur_node = cur_node->prev;
	}
	return (cur_node);
}

/**
 * @brief Iterate to last node of given list.
 *
 * @param lst 			List to be iterated through.
 * @return t_tkn_list* 	Last node of list or NULL if empty.
 */
t_tkn_list	*ft_last(t_tkn_list *lst)
{
	t_tkn_list	*last;

	last = lst;
	while (last)
	{
		if (last -> next == NULL)
			return (last);
		last = last -> next;
	}
	return (NULL);
}
