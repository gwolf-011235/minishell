/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:59:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 22:08:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

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
