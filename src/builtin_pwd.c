/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:59:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 18:45:49 by gwolf            ###   ########.fr       */
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
 */
void	ft_pwd(t_buf *buf)
{
	t_err	err;

	err = ft_create_pwd_value(buf);
	if (err != SUCCESS)
	{
		g_status = 1;
		return ;
	}
	errno = 0;
	ft_putendl_fd(buf->str, 1);
	if (errno != 0)
	{
		perror("minishell: pwd");
		g_status = 1;
		err = ERR_WRITE;
	}
	if (err == SUCCESS)
		g_status = 0;
}
