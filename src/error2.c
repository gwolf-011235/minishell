/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:56:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/23 20:40:39 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

t_err	ft_err_strdup(const char *src, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_strdup(src);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_err	ft_err_itoa(int n, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_itoa(n);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_err	ft_err_strjoin(const char s1, const char s2, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_strjoin(s1, s2);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

