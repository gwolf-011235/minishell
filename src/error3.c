/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 08:32:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 10:46:03 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

t_err	ft_err_open(const char *path, int flag, int *fd, char *msg)
{
	errno = 0;
	*fd = open(path, flag);
	if (*fd == -1)
	{
		perror(msg);
		return (ERR_OPEN);
	}
	return (SUCCESS);
}

t_err	ft_err_close(int fd, char *msg)
{
	int	ret;

	errno = 0;
	ret = close(fd);
	if (ret == -1)
	{
		perror(msg);
		return (ERR_CLOSE);
	}
	return (SUCCESS);
}

t_err	ft_err_pipe(int pipes[2], char *msg)
{
	int	ret;

	errno = 0;
	ret = pipe(pipes);
	if (ret == -1)
	{
		perror(msg);
		return (ERR_PIPE);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for execve to print error.
 * 
 * @param exec Executable string.
 * @param args Argument string array.
 * @param envp Env string array.
 */
void	ft_err_execve(char *exec, char **args, char **envp)
{
	int	ret;

	errno = 0;
	ret = execve(exec, args, envp);
	if (ret == -1)
		perror("minishell: child");
}
