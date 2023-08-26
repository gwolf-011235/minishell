/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 08:32:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 14:59:50 by gwolf            ###   ########.fr       */
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