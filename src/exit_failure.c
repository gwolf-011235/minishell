/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:57:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 19:17:42 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit_failure.c
 * @brief Contains failure function to cleanup
 */

#include "minishell.h"

void	ft_exit_failure(t_data *data, t_error exit_code)
{
	(void)exit_code;
	ft_hashtable_destroy(data->env_table);
	exit(errno);
}
