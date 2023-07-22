/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:15:09 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/22 14:15:10 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_utils.c
 * @brief Helper functions for parser.
 */

#include "mod_parser.h"

/**
 * @brief Iterate to last node of given list.
 * 
 * Returns 0 if list is empty.
 * @param cmd 		List of cmd-structures
 * @return t_cmd* 
 */
t_cmd	*ft_last_cmd(t_cmd *cmd)
{
	t_cmd	*last;

	last = cmd;
	while (last)
	{
		if (last -> next == NULL)
			return (last);
		last = last -> next;
	}
	return (0);
}
