/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:17:27 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/07 12:24:19 by sqiu             ###   ########.fr       */
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
/* 	if (local_err_count == 0)
		printf(GREEN"\nOK\n\n"RESET);
	else
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count); */
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
/* 	if (local_err_count == 0)
		printf(GREEN"\nOK\n\n"RESET);
	else
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count); */
	return (local_err_count);
}

static int	test_scmd_wrapper(char *testname, char *test)
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
	printf("Command:%s\n\n", test);
	ft_lex_input(&lst, test);
	ft_parser(lst, &cmd);
	ft_executor(cmd, envp);
	printf("\n");
/* 	while (cmd)
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
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count); */
	return (local_err_count);
}

static int	test_pipe_wrapper(char *testname, char *test)
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
	printf("Command:%s\n\n", test);
	ft_lex_input(&lst, test);
	ft_parser(lst, &cmd);
	ft_executor(cmd, envp);
	printf("\n");
/* 	while (cmd)
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
		printf(RED"\nKO:\t%d errors found\n\n"RESET, local_err_count); */
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

static void	test_singlecmds(void)
{
	//test_scmd_wrapper("scmd", "ls -la");
	//test_scmd_wrapper("scmd", "touch mimimi");
	//test_scmd_wrapper("scmd", "mkdir shubidu");
	//test_scmd_wrapper("scmd", "cp -v mimimi shubidu");
	//test_scmd_wrapper("scmd", "mv -v mimimi mumumu");
	//test_scmd_wrapper("scmd", "rm mumumu");
	//test_scmd_wrapper("scmd", "rm -r shubidu");
	//test_scmd_wrapper("scmd", "rm -r shubidu");
	//test_scmd_wrapper("scmd with infile", "cat <infile");
	//test_scmd_wrapper("scmd with infile and outfile", ">     outfile cat <infile");
	//test_scmd_wrapper("scmd with infile followed by heredoc", "cat <infile <<  supi");
	//test_scmd_wrapper("scmd with heredoc followed by infile", "cat  <<  supi  <infile");
	//test_scmd_wrapper("scmd with several infiles", "cat  <infile3  <infile <infile2");
	test_scmd_wrapper("scmd with several outfiles", "ls  >outfile3  >outfile >outfile2");
	test_scmd_wrapper("scmd with outfile in append mode", "cat infile >>outfile2");
}

static void	test_pipe(void)
{
	//test_pipe_wrapper("simple pipe", "ls -la | grep test");
	//test_pipe_wrapper("pipe with append", "ls -la | grep test | wc -l >>outfile2");
	//test_pipe_wrapper("pipe with individual infiles", "ls -la | <infile grep yo | <outfile wc -l");
	test_pipe_wrapper("pipe with individual plural infiles", "ls -la | <infile <infile2 grep yo | <outfile <infile3 wc -m");
}

void	test_executor(void)
{
	printf(YELLOW"*******TEST_EXECUTOR*******\n\n"RESET);
	//test_enum_cmds();
	//test_heredoc();
	//test_singlecmds();
	test_pipe();
}
