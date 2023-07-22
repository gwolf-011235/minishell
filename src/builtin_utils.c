/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 18:27:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_get_array_size(char **array, size_t *size)
{
	if (!array || !size)
		return (ERR_EMPTY);
	while (array[*size])
		(*size)++;
	return (SUCCESS);
}
