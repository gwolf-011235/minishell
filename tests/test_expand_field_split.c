/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_field_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:41:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 12:08:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_expand_field_split(void)
{
	t_tkn_list	*head;
	size_t		words;

	head = NULL;
	words = 0;
	ft_new_node(&head, ft_strdup("Hello my darling"));
	ft_field_split(&head, &words);
	test_print_tkn_list(head);
}
