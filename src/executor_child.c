/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:24:49 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/31 14:26:00 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_child.c
 * @brief Behaviour of child processes.
 */

#include "mod_executor.h"

/* This is the first command of the command chain. 

This function closes all unrequired file descriptors (all fd except
the two fd which are to replace stdin/stdout) and assigns the corresponding
file descriptors to stdin and stdout depending on the position of the
command in the chain.

	First command: stdin = fd_in, stdout = write end of first pipe

Afterwards these are closed as well and the command is being executed. */

void	firstborn(t_meta *meta, char **envp)
{
	do_close(meta->fd_out);
	do_close(meta->cmds[meta->i].fd[0]);
	replace_fd(meta->fd_in, meta->cmds[meta->i].fd[1]);
	do_close(meta->fd_in);
	do_close(meta->cmds[meta->i].fd[1]);
	if (execve(meta->cmds[meta->i].cmd, meta->cmds[meta->i].arg, envp) < 0)
	{
		pipinator(meta);
		mamma_mia(meta, ERR_FIRST);
	}
}

/* This is the last command of the command chain. 

This function closes all previous pipes except for the last pipe
connecting the last command to its predecessor. The write end of 
the last pipe is being closed. It assigns the corresponding
file descriptors to stdin and stdout depending on the position of the
command in the chain. 

	Last command: stdin = read end of previous pipe, stdout = fd_out

Afterwards these are closed as well and the command is being executed. */

void	lastborn(t_meta *meta, char **envp)
{
	int	j;

	do_close(meta->fd_in);
	j = -1;
	while (++j < meta->i - 1)
		plug_pipes(meta, j);
	do_close(meta->cmds[meta->i - 1].fd[1]);
	replace_fd(meta->cmds[meta->i - 1].fd[0], meta->fd_out);
	do_close(meta->fd_out);
	do_close(meta->cmds[meta->i - 1].fd[0]);
	if (execve(meta->cmds[meta->i].cmd, meta->cmds[meta->i].arg, envp) < 0)
	{
		pipinator(meta);
		mamma_mia(meta, ERR_LAST);
	}
}

/* This is a command in between the first and last. 

This function closes all previous pipes except for the last pipe
connecting the command to its predecessor. The write end of 
the previous pipe is being closed as well as the read end of
the current pipe. It assigns the corresponding
file descriptors to stdin and stdout depending on the position of the
command in the chain. 

	In between command: stdin = read end of previous pipe,
		stdout = write end of current pipe

Afterwards these are closed as well and the command is being executed. */

void	middle_child(t_meta *meta, char **envp)
{
	int	j;

	do_close(meta->fd_in);
	do_close(meta->fd_out);
	j = -1;
	while (++j < meta->i - 1)
		plug_pipes(meta, j);
	do_close(meta->cmds[meta->i - 1].fd[1]);
	do_close(meta->cmds[meta->i].fd[0]);
	replace_fd(meta->cmds[meta->i - 1].fd[0], meta->cmds[meta->i].fd[1]);
	do_close(meta->cmds[meta->i - 1].fd[0]);
	do_close(meta->cmds[meta->i].fd[1]);
	if (execve(meta->cmds[meta->i].cmd, meta->cmds[meta->i].arg, envp) < 0)
	{
		pipinator(meta);
		mamma_mia(meta, ERR_MID);
	}
}
