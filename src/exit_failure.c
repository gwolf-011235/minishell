/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:57:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 12:16:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_failure(t_data *data, t_error exit_code)
{
	(void)exit_code;
	ft_hashtable_destroy(data->env_table);
	exit(errno);
}