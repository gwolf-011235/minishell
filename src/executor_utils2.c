/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:24:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 16:27:20 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils2.c
 * @brief Helper functions for executor.
 */

#include "mod_executor.h"

/**
 * @brief Initialise executor by indexing.
 *
 * Second run assigns total number of cmds.
 * @param cmd 		List of cmds.
 */
void	ft_init_exec(t_cmd *cmd)
{
	int		count;
	t_cmd	*tmp;

	count = -1;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp->index = count;
		tmp = tmp->next;
	}
	while (cmd)
	{
		cmd->cmd_num = count + 1;
		cmd = cmd->next;
	}
}

/**
 * @brief Create all necessary pipes.
 *
 * Loop through cmd list and create pipe to connect cmds.
 * 		fd_pipe[0] refers to the read end of the pipe.
 * 		fd_pipe[1] refers to the write end of the pipe.
 * Data written to the write end of the pipe is buffered
 * by the kernel until it is read from the read end of the pipe.
 * Does not create pipe at last cmd.
 * Gives cmds the possibility to access pipe created in
 * predecessor.
 * @param cmd 		List of cmds.
 * @return t_err 	ERR_PIPE, SUCCESS
 */
t_err	ft_create_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->index < cmd->cmd_num - 1)
		{
			if (ft_err_pipe(cmd->fd_pipe, "minishell: pipe") == ERR_PIPE)
				return (ERR_PIPE);
			cmd->next->fd_prev_pipe[0] = cmd->fd_pipe[0];
			cmd->next->fd_prev_pipe[1] = cmd->fd_pipe[1];
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/**
 * @brief Check if PATH contains empty paths.
 *
 * If PATH="", first condition returns true.
 * If no colon is inside PATH, there is only one path
 * and the check returns false.
 *
 * Loop through the following:
 * Find colon inside of PATH.
 * If a colon is followed by another colon or \0, the
 * check returns true, otherwise false.
 * @param path_str 	String of paths optionally separated by colons.
 * @return true 	Empty path found.
 * @return false 	No empty paths found.
 */
bool	ft_check_empty_path(char *path_str)
{
	char	*tmp;

	if (!*path_str)
		return (true);
	tmp = path_str;
	if (*tmp == ':')
		return (true);
	while (*tmp)
	{
		tmp = ft_strchr(tmp, ':');
		if (!tmp)
			return (false);
		tmp++;
		if (*tmp == ':' || *tmp == '\0')
			return (true);
	}
	return (false);
}

/**
 * @brief Opens all saved outfiles of the cmd.
 *
 * Previous outfiles are closed again. Only the
 * last outfile is preserved.
 * Differentiates each outfile regarding append mode.
 * @param cmd 		Current cmd.
 */
void	ft_open_outfile(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->outfiles[++i])
	{
		if (cmd->fd_out > -1)
			ft_err_close(cmd->fd_out, "minishell: outfile");
		if (cmd->append_switches[i])
			cmd->fd_out = open(cmd->outfiles[i],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			cmd->fd_out = open(cmd->outfiles[i],
					O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (cmd->fd_out == -1)
		{
			cmd->execute = false;
			ft_print_warning(ERR_NO_DIR, cmd->outfiles[i]);
			break ;
		}
	}
}

/**
 * @brief Opens all outfiles of pipeline.
 *
 * @param cmd 		List of cmds in pipeline.
 */
void	ft_loop_thru_outfiles(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->outfiles)
			ft_open_outfile(cmd);
		cmd = cmd->next;
	}
}
