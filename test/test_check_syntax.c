/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:33:38 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/24 11:27:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_check_quote(void)
{
	const char	*test_quote[] = {
		"Hello",
		"\"Hello\"",
		"\"Hello\"\"How are you\"",
		"This is a long string with no quotes but beware: \"\". There were some",
		"\"Hello\" \"How are you",
		"\'I am fine thanks\'",
		"\'I am fine\" thanks\'",
		"\'I am fine thanks"

	};
	t_error		error;
	size_t		i;

	printf("\t\n** Quotes **\n\n");
	i = 0;
	while (i < 8)
	{
		printf("Input: %s\n", test_quote[i]);
		error = ft_check_syntax(test_quote[i]);
		if (error == SUCCESS)
			printf ("SUCCESS!\n");
		else if (error == ERR_SYNTAX)
			printf("Error Syntax\n");
		else
			printf("Wrong Error\n");
		printf("\n");
		i++;
	}
}

void	test_check_pipe(void)
{
	const char	*test_pipe[] = {
		"< Test | ls",
		"ls   |",
		"|",
		"hello | | bye",
		"hello || bye"
	};
	t_error		error;
	size_t		i;

	printf("\t\n** Pipes **\n\n");
	i = 0;
	while (i < 5)
	{
		printf("Input: %s\n", test_pipe[i]);
		error = ft_check_syntax(test_pipe[i]);
		if (error == SUCCESS)
			printf ("SUCCESS!\n");
		else if (error == ERR_SYNTAX)
			printf("Error Syntax\n");
		else
			printf("Wrong Error\n");
		printf("\n");
		i++;
	}
}

void	test_check_redirect(void)
{
	const char	*test_redirect[] = {
		"<file",
		"<< heredoc",
		"<  <",
		"<< >",
		"Spaces at the end: <  ",
		"Spaces at the end: <<   ",
		"<| test"
	};
	t_error		error;
	size_t		i;

	printf("\t\n** Redirect **\n\n");
	i = 0;
	while (i < 7)
	{
		printf("Input: %s\n", test_redirect[i]);
		error = ft_check_syntax(test_redirect[i]);
		if (error == SUCCESS)
			printf ("SUCCESS!\n");
		else if (error == ERR_SYNTAX)
			printf("Error Syntax\n");
		else
			printf("Wrong Error\n");
		printf("\n");
		i++;
	}
}

void	test_check_syntax(void)
{
	printf("\n\t*** test_check_syntax ***\n\n");
	test_check_quote();
	test_check_pipe();
	test_check_redirect();
}