/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:28:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/19 12:32:28 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "mod_handle_input.h"

static void	test_wrapper(char *name, char *str, t_buf *buf)
{
	t_tkn_list	*tmp;

	printf("TEST: %s\n", name);
	tmp = NULL;
	ft_lex_input(&tmp, str, buf);
	test_print_tkn_list(tmp);
	ft_free_lst(&tmp);
}

void	test_lexer(void)
{
	t_buf		buf;

	ft_buf_init(&buf);

	test_wrapper("Simple command: ls\n", "ls", &buf);
	test_wrapper("Simple command: ls with newline\n", "ls\n", &buf);
	test_wrapper("Simple command: ls -la with newline\n", "ls -la\n", &buf);
	test_wrapper("Simple command: ls                     -la with newline\n", "ls                     -la\n", &buf);
	test_wrapper("Simple command: <infile grep huhu >out with newline\n", "<infile grep huhu >out\n", &buf);
	test_wrapper("Simple command: <infile grep huhu | wc -l >out with newline\n", "<infile grep huhu | wc -l >out\n", &buf);
	test_wrapper("Simple command: <infile grep huhu|wc -l >out with newline\n", "<infile grep huhu|wc -l >out\n", &buf);
	test_wrapper("Simple command: < infile grep huhu|wc -l > out with newline\n", "< infile grep huhu|wc -l > out\n", &buf);
	test_wrapper("Simple command: < infile grep huhu|wc -l > out with newline\n", "< infile grep huhu|wc -l > out\n", &buf);
	test_wrapper("Simple command: <<delim grep huhu|wc -l >> out with newline\n", "<<delim grep huhu|wc -l >> out\n", &buf);
	test_wrapper("Simple command: export string=\"hello world\" with newline\n", "export string=\"hello world\"\n", &buf);
	test_wrapper("Simple command: \n~ $TEST\n", "~ $TEST", &buf);
}
