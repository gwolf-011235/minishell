/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:39:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 13:52:06 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_env.h"

t_err	ft_get_pid(int *pid)
{
	int		fd;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (ERR_MALLOC);
	*pid = ft_itoa(line);
	free(line);
	return (SUCCESS);
}

t_err	ft_create_env_pid(char **env_pid)
{
	t_err	err;
	int		pid;
	char	*tmp;

	pid = 0;
	err = ft_get_pid(&pid);
	if (err != SUCCESS)
		return (err);
	tmp = ft_atoi(pid);
	if (!tmp)
		return (ERR_MALLOC);
	*env_pid = ft_strjoin("$$=", tmp);
	free(tmp);
	if (!(*env_pid))
		return (ERR_MALLOC);
	return (SUCCESS);
}
