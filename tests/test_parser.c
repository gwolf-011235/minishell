/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:41:06 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/24 13:11:59 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern int			g_err_count;

static int	test_wrapper(char *testname, char *test, bool heredoc, bool append)
{
	int			local_err_count;
	int			i;
	t_tkn_list	*lst;
	t_cmd		*cmd;

	local_err_count = 0;
	i = 0;
	lst = NULL;
	cmd = NULL;
	printf("TEST: %s\n", testname);
	printf("Command:%s\n", test);
	ft_lex_input(&lst, test);
	ft_parser(lst, &cmd);
	while (cmd)
	{
		if (cmd->exe)
			printf(GREEN"\nexe: %s\n"RESET, cmd->exe);
		else
		{
			printf(RED"error: no exe\n"RESET);
			local_err_count++;
		}
		if (cmd->args)
		{
			printf(GREEN"args:\n"RESET);
			i = 0;
			while (cmd->args[i])
				printf(GREEN"\t%s\n"RESET, cmd->args[i++]);
		}
		else
		{
			printf(RED"error: no args\n"RESET);
			local_err_count++;
		}
		if (cmd->infile)
		{
			if (cmd->fd_in > 2)
			{
				printf (GREEN"infile fd: %d\n"RESET, cmd->fd_in);
				close(cmd->fd_in);
			}
			else
			{
				printf(RED"error: no fd_in\n"RESET);
				local_err_count++;
			}
		}
		if (cmd->outfile)
		{
			if (cmd->fd_out > 2)
			{
				printf (GREEN"outfile fd: %d\n"RESET, cmd->fd_out);
				close(cmd->fd_out);
			}
			else
			{
				printf(RED"error: no fd_out\n"RESET);
				local_err_count++;
			}
		}
		if (heredoc)
		{
			if (cmd->delim)
				printf(GREEN"delimiter: %s\n"RESET, cmd->delim);
			else
			{
				printf(RED"error: no delimiter\n"RESET);
				local_err_count++;
			}
		}
		if (append)
		{
			if (cmd->append)
				printf(GREEN"append mode set: %d\n"RESET, (int)cmd->append);
			else
			{
				printf(RED"error: no append mode\n"RESET);
				local_err_count++;
			}
		}
		cmd = cmd->next;
	}
	if (local_err_count == 0)
		printf(GREEN"\nOK\n\n"RESET);
	else
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count);
	return (local_err_count);
}


void	test_one_cmd(void)
{
	test_wrapper("One simple cmd", "< infile grep he -i > outfile", 0, 0);
	test_wrapper("One simple cmd", "ls < infile  > outfile -la", 0, 0);
}

void	test_two_cmds(void)
{
	test_wrapper("Two simple cmds", "ls <infile -la|>outfile wc -l ", 0, 0);
}

void	test_five_cmds(void)
{
	test_wrapper("Five simple cmds", "<   infile ls -la | grep chtulu | wc -m | cmd4 -weeee -o -asa| >outfile cmd5 ww 235", 0, 0);
}

void	test_parser(void)
{
	printf(YELLOW"*******TEST_PARSER*******\n\n"RESET);
	//test_one_cmd();
	//test_two_cmds();
	test_five_cmds();
	/* test_three_infiles();
	test_heredoc();
	test_three_outfiles();
	test_five_args(); */
}
