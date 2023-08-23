/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:56:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/23 10:59:55 by gwolf            ###   ########.fr       */
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


