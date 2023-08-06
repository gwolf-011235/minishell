/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:58:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 18:37:49 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern char			*g_string;
extern t_hashtable	*g_symtab;
extern int			g_err_count;

void	exec_expand_tkn_lst(t_tkn_list **head, t_data *data)
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_data *data)
void	test_expand_list(void)
{
	int			i;
	t_tkn_list	*tmp;

	test_setup_data();
	i = 1;
	printf(BLUE"**\tLIST\t**\n\n"RESET);
	g_string = "~ $TEST\n";
	ft_lex_input(&tmp, g_string);
	ft_expand_tkn_lst(&tmp, &g_data);
	while (tmp)
	{
		if (!strncmp(tmp->content, "\n", ft_strlen(tmp->content)))
			printf("%d: newline\n", i);
		else
			printf("%d: %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
}
