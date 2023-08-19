/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_field_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:41:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 12:34:56 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_expand_field_split(void)
{
	t_track		input;
	t_tkn_list	*head;
	t_buf		buf;

	head = NULL;
	ft_buf_init(&buf);
	ft_new_node(&head, ft_strdup("OLDEXPAND   Hello my darling$TEST"));
	ft_init_tracker(&input, head->content, ARG);
	ft_field_split(&input, &head, &buf);
	test_print_tkn_list(head);
}
