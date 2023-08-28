/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:16:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/28 17:51:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils3.c
 * @brief Helper functions for executor
 */

#include "mod_executor.h"

/**
 * @brief Sets exit status if last cmd of a pipeline
 * exited with ERR_UNKNOWN_CMD, ERR_NO_DIR or ERR_DIR.
 *
 * @param err ERR_UNKNOWN_CMD, ERR_NO_DIR or ERR_DIR
 */
void	ft_set_exit_status(t_err err)
{
	if (err == ERR_UNKNOWN_CMD || err == ERR_NO_DIR)
		g_status = 127;
	else if (err == ERR_DIR || err == ERR_PERM_DENIED)
		g_status = 126;
}

/**
 * @brief Checks if passed path has permission to be executed.
 *
 * @param rtrn 		Passed path.
 * @param args 		String array of args.
 * @return t_err 	ERR_PERM_DENIED, SUCCESS
 */
t_err	ft_check_permission(char *path, char **args)
{
	if (access(path, X_OK) == 0)
		return (SUCCESS);
	else
		return (ft_print_warning(ERR_PERM_DENIED, args[0]));
}

/**
 * @brief Check the exit status of child.
 *
 * Sets passed bool to false, if signal msg has already been printed. *
 * @param pid Pid of child.
 * @param print Pointer to print check bool.
 */
void	ft_check_exit_status(pid_t pid, bool *print)
{
	int		status;

	status = 0;
	(void)waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else
	{
		if (WIFSIGNALED(status))
		{
			g_status = 128 + WTERMSIG(status);
			if (__WCOREDUMP(status) && *print)
			{
				ft_putendl_fd("Quit (core dumped)", 2);
				*print = false;
			}
			else if (WTERMSIG(status) == SIGINT && *print)
			{
				ft_putchar_fd('\n', 2);
				*print = false;
			}
		}
	}
}
