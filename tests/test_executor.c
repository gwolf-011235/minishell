/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:27 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/07 10:55:19 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data		g_data;
extern int			g_err_count;
extern t_hashtable	*g_symtab;

static int	test_wrapper(char *testname, char *test)
{
	int			local_err_count;
	int			i;
	t_tkn_list	*lst;
	t_cmd		*cmd;
	char		**envp;

	local_err_count = 0;
	i = 0;
	lst = NULL;
	cmd = NULL;
	ft_env_setup(&g_symtab);
	ft_envp_create(g_symtab, &envp);
	printf("TEST: %s\n", testname);
	printf("Command:%s\n", test);
	ft_lex_input(&lst, test);
	ft_parser(lst, &cmd);
	ft_executor(cmd, envp);
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

static int	test_heredoc_wrapper(char *testname, char *test)
{
	int			local_err_count;
	int			i;
	t_tkn_list	*lst;
	t_cmd		*cmd;
	char		**envp;

	local_err_count = 0;
	i = 0;
	lst = NULL;
	cmd = NULL;
	ft_env_setup(&g_symtab);
	ft_envp_create(g_symtab, &envp);
	printf("TEST: %s\n", testname);
	printf("Command:%s\n", test);
	ft_lex_input(&lst, test);
	ft_parser(lst, &cmd);
	ft_init_exec(cmd);
	ft_handle_heredoc(cmd);
	while (cmd)
	{
		printf(GREEN"\ndelimiters:\n"RESET);
		i = 0;
		while (cmd->delims[i])
			printf(GREEN"\t%s\n"RESET, cmd->delims[i++]);
		printf("Infile: %d\n", cmd->fd_in);
		printf("Heredoc: %s\n", cmd->heredoc);
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
	test_wrapper("Five simple cmds", "<   infile ls -la | grep infile | wc -l  >outfile");
}

static void	test_heredoc(void)
{
	test_heredoc_wrapper("heredocs followed by infile", "<<samba <<gg <<yuhu grep bu <infile");
	test_heredoc_wrapper("infile followed by heredocs", "<<samba <infile <<gg <<yuhu grep bu");
	test_heredoc_wrapper("piped heredocs", "<<sa cat | <<gg grep bu");
}
void	test_executor(void)
{
	printf(YELLOW"*******TEST_EXECUTOR*******\n\n"RESET);
	//test_enum_cmds();
	test_heredoc();

}
