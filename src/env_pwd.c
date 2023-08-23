/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:15:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/23 09:26:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_pwd.c
 * @brief Functions relating to env_var $PWD.
 */

#include "mod_env.h"

/**
 * @brief Create string with the present working directory.
 *
 * Receives pointer to pointer to change value outside of function.
 * Return is t_err, so it can't return pointer itself.
 * Malloc string with 4096 and call getcwd for pwd.
 * If path is longer than size, free and malloc twice the size.
 * Repeat until path fits in array.
 *
 * @param pwd_value Pointer to pointer where to save string
 * @return t_err SUCCESS, ERR_MALLOC, ERR_CWD_FAIL.
 */
t_err	ft_create_pwd_value(t_buf *buf)
{
	t_err	err;

	while (1)
	{
		err = ft_err_getcwd(buf->str, buf->size,
				"minishell: ft_create_pwd_value");
		if (err == SUCCESS)
			break ;
		else if (err == ERR_CWD_BUF)
		{
			err = ft_buf_double(buf);
			if (err == ERR_MALLOC)
				return (ERR_MALLOC);
		}
		else
			return (ERR_CWD_FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Creates a new env_var PWD=path/to/pwd.
 *
 * Receives pointer to pointer to change value outside of function.
 * Return is t_err, so it can't return pointer itself.
 * Call ft_create_pwd_value to get right side of env_var.
 * If error passes on the error.
 * If success strjoin with left side.
 *
 * @param pwd Pointer to pointer where to save string.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_CWD_FAIL
 */
t_err	ft_create_env_pwd(char **pwd, t_buf *buf)
{
	t_err	err;

	ft_buf_clear(buf);
	err = ft_create_pwd_value(buf);
	if (err != SUCCESS)
		return (err);
	errno = 0;
	*pwd = ft_strjoin("PWD=", buf->str);
	if (*pwd == NULL)
	{
		perror("minishell: ft_create_env_pwd");
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

/**
 * @brief Creates and inserts the env_var PWD.
 *
 * If no PWD is present in env_table, this function inserts.
 * @param data
 * @return t_err SUCCESS, ERR_MALLOC, ERR_CWD_FAIL, ERR_HT_NO_INSERT,
 * ERR_EMPTY, ERR_NOT_FOUND
 */
t_err	ft_insert_env_pwd(t_hashtable *env_table, t_buf *buf)
{
	char	*pwd;
	t_err	err;

	pwd = NULL;
	err = ft_create_env_pwd(&pwd, buf);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_insert_export(env_table, pwd, 3, true);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
