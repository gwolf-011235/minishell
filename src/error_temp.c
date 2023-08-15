/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:42:58 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 10:50:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "libft.h"
#include <unistd.h>

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
