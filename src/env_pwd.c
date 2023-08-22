/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:15:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/22 18:44:07 by gwolf            ###   ########.fr       */
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
t_err	ft_create_pwd_value(char **pwd_value)
{
	size_t	size;

	size = 4096;
	while (1)
	{
		*pwd_value = malloc(size);
		if (*pwd_value == NULL)
			return (ERR_MALLOC);
		if (getcwd(*pwd_value, size) != NULL)
			break ;
		else
		{
			free(*pwd_value);
			if (errno == ERANGE)
			{
				size *= 2;
				continue ;
			}
			else
				return (ERR_CWD_FAIL);
		}
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
t_err	ft_create_env_pwd(char **pwd)
{
	t_err	err;
	char	*pwd_value;

	pwd_value = NULL;
	err = ft_create_pwd_value(&pwd_value);
	if (err != SUCCESS)
		return (err);
	*pwd = ft_strjoin("PWD=", pwd_value);
	free(pwd_value);
	if (*pwd == NULL)
		return (ERR_MALLOC);
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
t_err	ft_insert_env_pwd(t_hashtable *env_table)
{
	char	*pwd;
	t_err	err;

	pwd = NULL;
	err = ft_create_env_pwd(&pwd);
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_insert_export(env_table, pwd, 3, true);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
