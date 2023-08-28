/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:05 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/28 17:29:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief Functions to execute the list of cmds.
 */

#include "mod_executor.h"

/**
 * @brief Driver function to execute list of cmds.
 *
 * Index the list of cmds.
 *
 * If heredocs are present in cmd, they are opened
 * and take input from stdin. In case a heredoc is the
 * last infile redirect, its fd is given to the cmd.
 * Differentiate between ERR_ABORT (Cancel whole executor)
 * and ERR_HEREDOC_EOF (Continue executor).
 *
 * All necessary pipes are created in advance to ensure
 * definite fd assignment to all pipe ends.
 *
 * Get PATH from envp and save it into paths.
 * If no path is found (ERR_NOPATH), try to execute
 * cmd nonetheless in the current directory.
 *
 * If cmd list only contains one entry, call ft_execute_scmd(),
 * else call ft_execute_pcmds().
 *
 * If one of both functions returns ERR_MALLOC, ERR_STAT or ERR_FORK,
 * print err message and exit the executor.
 *
 * If the last executed cmd of a pipeline returns with ERR_UNKNOWN_CMD,
 * ERR_NO_DIR or ERR_DIR, set the exit status to the according value
 * as it has been overwritten by ft_wait_for_babies().
 * @param cmd 		List of cmds.
 * @param envp 		String array with env variables.
 * @param data		Data struct containing the env.
 * @return t_err 	ERR_EXECUTOR, ERR_PIPE, SUCCESS
 */
t_err	ft_executor(t_cmd *cmd, t_data *data)
{
	t_err	err;
	char	**paths;
	bool	empty_path;

	paths = NULL;
	empty_path = false;
	ft_init_exec(cmd);
	err = ft_handle_heredoc(cmd, data->env_table, data->prompt2);
	if (err != SUCCESS)
		return (ft_err_executor(cmd, paths, err));
	if (ft_create_pipes(cmd) == ERR_PIPE)
		return (ft_err_executor(cmd, paths, err));
	if (ft_get_path(data->envp, &paths, &empty_path) == ERR_MALLOC)
		return (ft_err_executor(cmd, paths, err));
	if (cmd->next == NULL)
		err = ft_execute_scmd(cmd, paths, data, empty_path);
	else
		err = ft_execute_pcmds(cmd, paths, data, empty_path);
	if (err == ERR_FORK || err == ERR_STAT || err == ERR_MALLOC)
		return (ft_err_executor(cmd, paths, err));
	if (err == ERR_UNKNOWN_CMD || err == ERR_NO_DIR || err == ERR_DIR
		|| err == ERR_PERM_DENIED)
		ft_set_exit_status(err);
	ft_cleanup_cmd_list(cmd, paths);
	return (SUCCESS);
}

/**
 * @brief Executes single cmd provided.
 *
 * @param cmd 			Cmd to be processed.
 * @param paths			String array of all system bin paths.
 * @param data			Data struct containing the env.
 * @param empty_path	Boolean to determine if PATH contained empty paths.
 * @return t_err 		ERR_FORK, ERR_MALLOC, ERR_STAT,
 * 						ERR_UNKNOWN_CMD, ERR_DIR, ERR_NO_DIR, SUCCESS
 */
t_err	ft_execute_scmd(t_cmd *cmd, char **paths, t_data *data, bool empty_path)
{
	t_err	err;

	if (cmd->outfiles)
		ft_open_outfile(cmd);
	if (cmd->args && cmd->execute)
	{
		if (ft_check_builtin(cmd->args[0]))
			return (ft_execute_builtin(0, cmd, data));
		err = ft_check_cmd_access(cmd->args, paths, empty_path);
		if (err != SUCCESS)
			return (err);
		if (ft_create_child(cmd, data, false) == ERR_FORK)
			return (ERR_FORK);
		ft_wait_for_babies(cmd);
	}
	else
	{
		if (!cmd->execute)
			g_status = 1;
		ft_close(&cmd->fd_in);
		ft_close(&cmd->fd_out);
	}
	return (SUCCESS);
}

/**
 * @brief Executes list of cmds provided.
 *
 * Iterate through the cmd list:
 * 	Check for built-ins.
 * 	If yes, execute built-in and move onto next cmd.
 * 	If no, check for system call by verifying its accessibility.
 * 	On success system call is executed in child process.
 * 	On failure error message is printed.
 * After all cmds/children are launched, the parent waits for
 * each termination.
 * @param cmd 			List of cmds.
 * @param paths			String array of all system bin paths.
 * @param data			Data struct containing the env.
 * @param empty_path	Boolean to determine if PATH contained empty paths.
 * @return t_err 		ERR_MALLOC, ERR_STAT, ERR_FORK,
 * 						ERR_UNKNOWN_CMD, ERR_DIR, ERR_NO_DIR, SUCCESS
 */
t_err	ft_execute_pcmds(t_cmd *cmd,
	char **paths, t_data *data, bool empty_path)
{
	t_err	err;
	t_cmd	*tmp;

	tmp = cmd;
	err = SUCCESS;
	ft_loop_thru_outfiles(cmd);
	while (cmd && cmd->index < cmd->cmd_num)
	{
		if (cmd->args && cmd->execute)
		{
			err = ft_execute_cmd(cmd, data, empty_path, paths);
			if (err == ERR_MALLOC || err == ERR_STAT || err == ERR_FORK)
				return (err);
			else if (err == ERR_IS_CHILD)
				break ;
			else
				ft_close_iopp(cmd);
		}
		else
			ft_close_iopp(cmd);
		cmd = cmd->next;
	}
	if (err != ERR_IS_CHILD)
		ft_wait_for_babies(tmp);
	return (err);
}

/**
 * @brief Differentiates between builtins and system calls and executes.
 *
 * @param cmd			Current cmd.
 * @param data			Overarching data struct.
 * @param empty_path	Boolean to determine if PATH contained empty paths.
 * @param paths			String array of all system bin paths.
 * @return t_err		ERR_FORK, ERR_IS_CHILD, ERR_UNKNOWN_CMD,
 *						ERR_MALLOC, SUCCESS, ERR_STAT, ERR_DIR, ERR_NO_DIR
 */
t_err	ft_execute_cmd(t_cmd *cmd, t_data *data, bool empty_path, char **paths)
{
	t_err	err;

	if (ft_check_builtin(cmd->args[0]))
	{
		if (ft_execute_builtin(1, cmd, data) == ERR_FORK)
			return (ERR_FORK);
		if (cmd->pid == 0)
			return (ERR_IS_CHILD);
	}
	else
	{
		err = ft_check_cmd_access(cmd->args, paths, empty_path);
		if (err != SUCCESS)
			return (err);
		if (ft_create_child(cmd, data, false) == ERR_FORK)
			return (ERR_FORK);
	}
	return (SUCCESS);
}

/**
 * @brief Check whether the argument is a directory.
 *
 * Stat() returns 0 if a directory was found, else -1.
 * @param args 		Argument array containing the cmd.
 * @return t_err 	ERR_DIR, ERR_NO_DIR, ERR_STAT, SUCCESS
 */
t_err	ft_check_dir(char **args)
{
	struct stat	buf;
	t_err		err;

	err = ft_err_stat(args[0], &buf, "minishell: stat");
	if (err != SUCCESS)
		return (err);
	if (S_ISDIR(buf.st_mode))
		return (ERR_DIR);
	else
		return (SUCCESS);
}
