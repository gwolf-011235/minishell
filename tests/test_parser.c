/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:41:06 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/19 12:50:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern int			g_err_count;

static int	test_wrapper(char *testname, char *test, bool heredoc, bool append, t_buf *buf)
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
	ft_lex_input(&lst, test, buf);
	ft_parser(lst, &cmd);
	while (cmd)
	{
		if (cmd->args)
		{
			printf(GREEN"\nargs:\n"RESET);
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
			if (cmd->delims)
			{
				printf(GREEN"delimiters:\n"RESET);
				i = 0;
				while (cmd->delims[i])
					printf(GREEN"\t%s\n"RESET, cmd->delims[i++]);
			}
			else
			{
				printf(RED"error: no delimiter\n"RESET);
				local_err_count++;
			}
		}
		if (append)
		{
			int i = -1;
			while (++i < cmd->out_pos)
			{
				if (cmd->append_switches[i])
					printf(GREEN"append mode set: %d\n"RESET, (int)cmd->append_switches[i]);
				else
				{
					printf(RED"error: no append mode\n"RESET);
					local_err_count++;
				}
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


void	test_one_cmd(t_buf *buf)
{
	test_wrapper("One simple cmd", "< infile grep he -i > outfile", 0, 0, buf);
	//test_wrapper("One simple cmd", "ls < infile  > outfile -la", 0, 0);
}

void	test_two_cmds(t_buf *buf)
{
	test_wrapper("Two simple cmds", "ls <infile -la|>outfile wc -l ", 0, 0, buf);
}

void	test_five_cmds(t_buf *buf)
{
	test_wrapper("Five simple cmds", "<   infile ls -la | grep chtulu | wc -m | cmd4 -weeee -o -asa| >outfile cmd5 ww 235", 0, 0, buf);
}

void	test_three_infiles(t_buf *buf)
{
	test_wrapper("Three infiles", "grep <infile < infile2 mammmmamia <infile3", 0, 0, buf);
}

void	test_heredoc(t_buf *buf)
{
	test_wrapper("Heredoc", "<< EOF wc -l >outfile", 1, 0, buf);
}

void	test_three_heredocs(t_buf *buf)
{
	test_wrapper("Three heredocs", "<< EOF wc <<mimi -l << siuuu >outfile", 1, 0, buf);
}

void	test_three_outfiles(t_buf *buf)
{
	test_wrapper("Three outfiles", "echo >outfile > outfile2 mammmmamia >outfile3", 0, 0, buf);
}

void	test_append(t_buf *buf)
{
	test_wrapper("Append", "<infile wc -l >>outfile", 0, 1, buf);
}

void	test_parser(void)
{
	t_buf	buf;

	ft_buf_init(&buf);
	printf(YELLOW"*******TEST_PARSER*******\n\n"RESET);
	test_one_cmd(&buf);
	test_two_cmds(&buf);
	test_five_cmds(&buf);
	test_three_infiles(&buf);
	test_heredoc(&buf);
	test_three_heredocs(&buf);
	test_three_outfiles(&buf);
	test_append(&buf);
	ft_buf_destroy(&buf);
}
