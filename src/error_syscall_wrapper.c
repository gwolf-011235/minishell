/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syscall_wrapper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:57:23 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/27 18:31:32 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_syscall_wrapper.c
 * @brief Wrapper functions to print error messages with perror for syscalls.
 */
#include "minishell_error.h"

/**
 * @brief Wrapper function for write to print error.
 * 
 * @param fd 		File descriptor to be written to.
 * @param str		String to write.
 * @param msg		Message for perror.
 * @return t_err 	ERR_WRITE, SUCCESS
 */
t_err	ft_err_write(int fd, char *str, char *msg)
{
	int	ret;

	errno = 0;
	ret = write(fd, str, ft_strlen(str));
	if (ret == -1)
	{
		perror(msg);
		return (ERR_WRITE);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for chdir to print error.
 * 
 * @param path		Path string to change to.
 * @param msg		Message for perror.
 * @return t_err 	ERR_CHDIR_FAIL, SUCCESS
 */
t_err	ft_err_chdir(char *path, char *msg)
{
	int	ret;

	errno = 0;
	ret = chdir(path);
	if (ret == -1)
	{
		ft_putstr_fd(msg, 2);
		perror(path);
		return (ERR_CHDIR_FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for stat to print error.
 *
 * @param pathname		Path to verify.
 * @param statbuf		Buffer for stat result.
 * @param msg			Message for perror.
 * @return t_err		ERR_NO_DIR, ERR_STAT; SUCCESS
 */
t_err	ft_err_stat(const char *pathname, struct stat *statbuf, char *msg)
{
	int	ret;

	errno = 0;
	ret = stat(pathname, statbuf);
	if (ret == -1)
	{
		if (errno == ENOENT)
			return (ERR_NO_DIR);
		else
		{
			perror(msg);
			return (ERR_STAT);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for malloc to print error.
 * 
 * @param ptr		Pointer to pointer to be malloced.
 * @param size		Size of malloc.
 * @param msg		Message for perror.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_err_malloc(void **ptr, size_t size, char *msg)
{
	errno = 0;
	*ptr = malloc(size);
	if (*ptr == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for getcwd to print error.
 * 
 * @param buf		Buffer string to which currrent working directory is copied.
 * @param size		Size of buffer string.
 * @param msg		Message for perror.
 * @return t_err 	ERR_CWD_BUF, ERR_CWD_FAIL, SUCCESS
 */
t_err	ft_err_getcwd(char *buf, size_t size, char *msg)
{
	errno = 0;
	if (getcwd(buf, size) == NULL)
	{
		if (errno == ERANGE)
			return (ERR_CWD_BUF);
		else
		{
			perror(msg);
			return (ERR_CWD_FAIL);
		}
	}
	return (SUCCESS);
}
