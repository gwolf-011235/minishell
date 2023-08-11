/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:32:57 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/09 00:04:20 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleanup.c
 * @brief General functions to clean up the program.
 */

#include "mod_cleanup.h"

/**
 * @brief Frees a NULL-terminated string array and its strings.
 * 
 * @param arr String array to be freed.
 */
void	ft_free_str_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
