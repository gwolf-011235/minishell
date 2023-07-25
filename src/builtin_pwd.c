/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:59:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 23:49:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_pwd.c
 * @brief Implementation of builtin pwd.
 */
#include "mod_builtin.h"

/**
 * @brief Print working directory.
 *
 * Create str of working directory with ft_create_pwd_value().
 * Print it and free str.
 *
 * @return t_err SUCCESS, ERR_MALLOC, ERR_CWD_FAIL.
 */
t_err	ft_pwd(void)
{
	char	*pwd;
	t_err	err;

	pwd = NULL;
	err = ft_create_pwd_value(&pwd);
	if (err != SUCCESS)
		return (err);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
