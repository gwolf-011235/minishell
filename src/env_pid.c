/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:39:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/22 18:38:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_pid.c
 * @brief Functions relating to env_var $$
 */
#include "mod_env.h"

/**
 * @brief Retrieve pid for current process.
 *
 * /proc/self/stat provides status information about the process.
 * /self/ is a magic link pointing to the calling process.
 * Open, read with get_next_line().
 * First number corresponds to pid. Convert with ft_atoi().
 * @param pid Pointer to int where to save.
 * @return t_err SUCCESS, ERR_OPEN, ERR_MALLOC
 */
t_err	ft_get_pid_value(pid_t *pid)
{
	int		fd;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (ERR_OPEN);
	line = get_next_line(fd);
	if (!line)
		return (ERR_MALLOC);
	*pid = ft_atoi(line);
	free(line);
	return (SUCCESS);
}

/**
 * @brief Creates env_var $$=PID.
 *
 * @param env_pid Where to save env_str
 * @return t_err SUCCESS, ERR_OPEN, ERR_MALLOC
 */
t_err	ft_create_env_pid(char **env_pid)
{
	t_err	err;
	pid_t	pid;
	char	*tmp;

	pid = 0;
	err = ft_get_pid_value(&pid);
	if (err != SUCCESS)
		return (err);
	tmp = ft_itoa(pid);
	if (!tmp)
		return (ERR_MALLOC);
	*env_pid = ft_strjoin("$=", tmp);
	free(tmp);
	if (!(*env_pid))
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var $$.
 *
 * @param env_table Environment.
 * @return SUCCESS, ERR_MALLOC
 */
t_err	ft_insert_env_pid(t_hashtable *env_table)
{
	char	*pid;
	t_err	err;

	pid = NULL;
	err = ft_create_env_pid(&pid);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_insert(env_table, pid, 1, true);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
