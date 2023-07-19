/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:28:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/19 23:51:29 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "../inc/lexer_list.h"
#include "../inc/lexer_tok.h"

void	test_lexer(void)
{
	t_data		*data;
	char		*str;
	t_tkn_list	*tmp;

	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	data->lst_head = NULL;

	printf("\nSimple command: ls\n");
	str = "ls";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: ls with newline\n");
	str = "ls\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: ls -la with newline\n");
	str = "ls -la\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: ls                     -la with newline\n");
	str = "ls                     -la\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: <infile grep huhu >out with newline\n");
	str = "<infile grep huhu >out\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: <infile grep huhu | wc -l >out with newline\n");
	str = "<infile grep huhu | wc -l >out\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: <infile grep huhu|wc -l >out with newline\n");
	str = "<infile grep huhu|wc -l >out\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: < infile grep huhu|wc -l > out with newline\n");
	str = "< infile grep huhu|wc -l > out\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: <<delim grep huhu|wc -l >> out with newline\n");
	str = "<<delim grep huhu|wc -l >> out\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\nSimple command: export string=\"hello world\" with newline\n");
	str = "export string=\"hello world\"\n";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	printf("\n~ $TEST\n");
	str = "~ $TEST";
	ft_list_token(data, str);
	tmp = data->lst_head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&data->lst_head);

	free(data);
}
