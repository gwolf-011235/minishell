/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:28:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 14:13:15 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "mod_handle_input.h"

void	test_lexer(void)
{
	char		*str;
	t_tkn_list	*tmp;

	tmp = NULL;

	printf("\nSimple command: ls\n");
	str = "ls";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: ls with newline\n");
	str = "ls\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: ls -la with newline\n");
	str = "ls -la\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: ls                     -la with newline\n");
	str = "ls                     -la\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: <infile grep huhu >out with newline\n");
	str = "<infile grep huhu >out\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: <infile grep huhu | wc -l >out with newline\n");
	str = "<infile grep huhu | wc -l >out\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: <infile grep huhu|wc -l >out with newline\n");
	str = "<infile grep huhu|wc -l >out\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: < infile grep huhu|wc -l > out with newline\n");
	str = "< infile grep huhu|wc -l > out\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: <<delim grep huhu|wc -l >> out with newline\n");
	str = "<<delim grep huhu|wc -l >> out\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\nSimple command: export string=\"hello world\" with newline\n");
	str = "export string=\"hello world\"\n";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);

	printf("\n~ $TEST\n");
	str = "~ $TEST";
	ft_lex_input(tmp, str);
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_free_lst(&tmp);
}
