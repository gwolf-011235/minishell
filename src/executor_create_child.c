/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_create_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 20:26:53 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_create_child.c
 * @brief Functions to create child processes.
 */

#include "mod_executor.h"

/* This function distinguishes between the position of the command needing
to be executed and creates the pertinent child. */

void	ft_create_child(t_cmd *cmd, char **envp)
{
	if (cmd->index == 0)
		ft_raise_first(cmd, envp);
	else if (cmd->index == cmd->cmd_num - 1)
		ft_raise_last(cmd, envp);
	else
		ft_raise_middle(cmd, envp);
}

/* This function creates a child by forking and calls the pertinent
function which is to be executed by the child. The parent does not wait
for the child to finish (flag WNOHANG set), but retrieves its pid when
its done. The parent closes the fd which are duplicated and used by the child.
*/

void	ft_raise_first(t_cmd *cmd, char **envp)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		ft_plug_pipe(cmd, 0);
		return (ERR_FORK);
	}
	else if (cmd->pid == 0)
		ft_firstborn(cmd, envp);
	if (waitpid(cmd->pid, NULL, WNOHANG) < 0)
		return (ERR_FIRST);
	ft_plug_pipe(cmd, 0);
	cmd->fd_pipe[1] = -1;
}

/* This function creates a child by forking and calls the pertinent
function which is to be executed by the child. The parent waits
for the child to finish (no flags set) and retrieves its pid when
its done. This prohibits the parent to terminate before
the child has finished. 
The parent closes the fd which are duplicated and used by the child. 
*/

void	ft_raise_last(t_cmd *cmd, char **envp)
{
	meta->cmds[meta->i].pid = fork();
	if (meta->cmds[meta->i].pid < 0)
		no_senor(meta, ERR_FORK);
	else if (meta->cmds[meta->i].pid == 0)
		lastborn(meta, envp);
	if (waitpid(meta->cmds[meta->i].pid, NULL, 0) < 0)
		mamma_mia(meta, ERR_LAST);
	if (close(meta->fd_out) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->fd_out = -1;
	if (close(meta->cmds[meta->i - 1].fd[0]) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->cmds[meta->i - 1].fd[0] = -1;
}

/* This function creates a child by forking and calls the pertinent
function which is to be executed by the child. The parent does not wait
for the child to finish (flag WNOHANG set), but retrieves its pid when
its done. The parent closes the fd which are duplicated and used by the child.
*/

void	ft_raise_middle(t_cmd *cmd, char **envp)
{
	meta->cmds[meta->i].pid = fork();
	if (meta->cmds[meta->i].pid < 0)
		no_senor(meta, ERR_FORK);
	else if (meta->cmds[meta->i].pid == 0)
		middle_child(meta, envp);
	if (waitpid(meta->cmds[meta->i].pid, NULL, WNOHANG) < 0)
		mamma_mia(meta, ERR_MID);
	if (close(meta->cmds[meta->i - 1].fd[0]) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->cmds[meta->i - 1].fd[0] = -1;
	if (close(meta->cmds[meta->i].fd[1]) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->cmds[meta->i].fd[1] = -1;
}
