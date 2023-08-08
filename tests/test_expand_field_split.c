/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_field_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:41:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/08 09:40:28 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_expand_field_split(void)
{
	t_track		input;
	t_tkn_list	*head;

	head = NULL;
	ft_new_node(&head, ft_strdup("OLDEXPAND   Hello my darling$TEST"));
	ft_init_tracker(&input, head->content);
	ft_field_split(&input, &head);
	test_print_tkn_list(head);
}
