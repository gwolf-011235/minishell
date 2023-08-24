/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:39:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 12:49:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_pid.c
 * @brief Functions relating special params $ and 0.
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

	if (ft_err_open("/proc/self/stat", O_RDONLY, &fd,
			"Could not open /proc/self/stat") != SUCCESS)
		return (ERR_OPEN);
	errno = 0;
	line = get_next_line(fd);
	if (!line)
	{
		perror("minishell: startup");
		(void)ft_err_close(fd, "Could not close /proc/self/status");
		return (ERR_MALLOC);
	}
	(void)ft_err_close(fd, "Could not close /proc/self/status");
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
	tmp = NULL;
	if (ft_err_itoa(pid, &tmp, "minishell: startup") == ERR_MALLOC)
		return (ERR_MALLOC);
	err = ft_err_strjoin("$=", tmp, env_pid, "minishell: startup");
	free(tmp);
	return (err);
}

/**
 * @brief Creates and inserts the env_var $$.
 *
 * @param env_table Environment.
 * @return SUCCESS, ERR_MALLOC, ERR_OPEN
 */
t_err	ft_insert_env_pid(t_hashtable *env_table)
{
	char	*pid;
	t_err	err;

	pid = NULL;
	err = ft_create_env_pid(&pid);
	if (err != SUCCESS)
		return (err);
	errno = 0;
	err = ft_hashtable_insert(env_table, pid, 1, true);
	if (err == ERR_MALLOC)
		perror("minishell: startup");
	if (err == ERR_MALLOC || err == ERR_HT_NO_INSERT)
		free(pid);
	return (err);
}

/**
 * @brief Creates and inserts special $0
 *
 * @param env_table Environment.
 * @param argv_zero Argv on pos 0
 * @return t_err SUCCES, ERR_MALLOC, ERR_HT_NO_INSERT
 */
t_err	ft_insert_env_zero(t_hashtable *env_table, char *argv_zero)
{
	t_err	err;
	char	*env_zero;

	env_zero = NULL;
	if (ft_err_strjoin("0=", argv_zero, &env_zero,
			"minishell: startup") == ERR_MALLOC)
		return (ERR_MALLOC);
	errno = 0;
	err = ft_hashtable_insert(env_table, env_zero, 1, true);
	if (err == ERR_MALLOC)
		perror("minishell: startup");
	if (err == ERR_MALLOC || err == ERR_HT_NO_INSERT)
		free(env_zero);
	return (err);
}

/**
 * @brief Inserts parameters $0 and $$ into environment.
 *
 * $0 = shell name.
 * $$ = pid of shell instance.
 * @param env_table Environment.
 * @param argv_zero First arg of argv.
 */
void	ft_set_special_params(t_hashtable *env_table, char *argv_zero)
{
	if (ft_insert_env_zero(env_table, argv_zero) != SUCCESS)
		ft_putendl_fd("minishell: warning: $0 not created", 2);
	if (ft_insert_env_pid(env_table) != SUCCESS)
		ft_putendl_fd("minishell: warning: $0 not created", 2);
}
