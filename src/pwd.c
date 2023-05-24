/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:15:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 14:04:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	ft_create_pwd_value(char *pwd_value)
{
	size_t	size;

	size = 4096;
	while (1)
	{
		pwd_value = malloc(size);
		if (pwd_value == NULL)
			return (ERR_MALLOC);
		if (getcwd(pwd_value, size) != NULL)
			break ;
		else
		{
			free(pwd_value);
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

t_error	ft_create_pwd_str(char *pwd)
{
	t_error	err;
	char	*pwd_value;

	pwd_value = NULL;
	err = ft_create_pwd_value(pwd_value);
	if (err != SUCCESS)
		return (err);
	pwd = ft_strjoin("PWD=", pwd_value);
	free(pwd_value);
	if (!pwd)
		return (ERR_MALLOC);
	return (SUCCESS);
}