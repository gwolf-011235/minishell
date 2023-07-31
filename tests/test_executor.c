/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:27 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/31 13:29:17 by sqiu             ###   ########.fr       */
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
	ft_executor(cmd);
	while (cmd)
	{
		printf("\nCurrent index: %d\n", cmd->index);
		printf("Total cmds: %d\n", cmd->cmd_num);
		cmd = cmd->next;
	}
	if (local_err_count == 0)
		printf(GREEN"\nOK\n\n"RESET);
	else
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count);
	return (local_err_count);
}
static void	test_enum_cmds(void)
{
	test_wrapper("Five simple cmds", "<   infile ls -la | grep chtulu | wc -m | cmd4 -weeee -o -asa| >outfile cmd5 ww 235", 0, 0);
}

void	test_executor(void)
{
	printf(YELLOW"*******TEST_EXECUTOR*******\n\n"RESET);
	test_enum_cmds();

}
