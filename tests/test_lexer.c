/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:28:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/08 17:26:39 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_list.h"

void	test_lexer(void)
{
	t_data		data;
	char		*str;
	t_tkn_list	*tmp;

	data.lst_head = NULL;

	// Simple command: ls
	printf("\nSimple command: ls\n");
	str = "ls\n";
	ft_list_token(&data, str);
	tmp = data.lst_head;
	while (tmp)
	{
		printf("%s", (char *)tmp->content);
		tmp = tmp->next;
	}
}
