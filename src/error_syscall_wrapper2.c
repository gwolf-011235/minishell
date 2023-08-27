/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syscall_wrapper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 08:32:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 18:39:57 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_syscall_wrapper2.c
 * @brief Wrapper functions to print error messages with perror for syscalls.
 */
#include "minishell_error.h"

/**
 * @brief Wrapper function for open to print error.
 * 
 * @param path		Path string to file to open.
 * @param flag		Flags given to open().
 * @param fd		File descriptor to assign to opened file.
 * @param msg		Message for perror.
 * @return t_err 	ERR_OPEN, SUCCESS
 */
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

/**
 * @brief Wrapper function for close to print error.
 * 
 * @param fd		File descriptor of file to be closed.
 * @param msg		Message for perror.
 * @return t_err 	ERR_CLOSE, SUCCESS
 */
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

/**
 * @brief Wrapper function for pipe to print error.
 * 
 * @param pipes		Integer array in which to save fds of created 
 * pipe ends.
 * @param msg		Message for perror.
 * @return t_err 	ERR_PIPE, SUCCESS
 */
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
