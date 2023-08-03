/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_create_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/31 14:23:59 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_create_child.c
 * @brief Functions to create child processes.
 */

#include "mod_executor.h"

/* This function distinguishes between the position of the command needing
to be executed and creates the pertinent child. */

void	create_child(t_meta *meta, char **envp)
{
	if (meta->i == 0)
		raise_first(meta, envp);
	else if (meta->i == meta->cmd_num - 1)
		raise_last(meta, envp);
	else
		raise_middle(meta, envp);
}

/* This function creates a child by forking and calls the pertinent
function which is to be executed by the child. The parent does not wait
for the child to finish (flag WNOHANG set), but retrieves its pid when
its done. The parent closes the fd which are duplicated and used by the child.
*/

void	raise_first(t_meta *meta, char **envp)
{
	meta->cmds[meta->i].pid = fork();
	if (meta->cmds[meta->i].pid < 0)
		no_senor(meta, ERR_FORK);
	else if (meta->cmds[meta->i].pid == 0)
		firstborn(meta, envp);
	if (waitpid(meta->cmds[meta->i].pid, NULL, WNOHANG) < 0)
		mamma_mia(meta, ERR_FIRST);
	if (meta->fd_in > 0 && close(meta->fd_in) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->fd_in = -1;
	if (close(meta->cmds[meta->i].fd[1]) < 0)
		mamma_mia(meta, ERR_CLOSE);
	meta->cmds[meta->i].fd[1] = -1;
}

/* This function creates a child by forking and calls the pertinent
function which is to be executed by the child. The parent waits
for the child to finish (no flags set) and retrieves its pid when
its done. This prohibits the parent to terminate before
the child has finished. 
The parent closes the fd which are duplicated and used by the child. 
*/

void	raise_last(t_meta *meta, char **envp)
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

void	raise_middle(t_meta *meta, char **envp)
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
