/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:57:23 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/21 17:16:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

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
