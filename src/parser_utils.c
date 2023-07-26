/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:15:09 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/27 00:57:09 by sqiu             ###   ########.fr       */
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
 * @param cmd_head 		List of cmd-structures
 * @return t_cmd* 
 */
t_cmd	*ft_last_cmd(t_cmd *cmd_head)
{
	t_cmd	*last;

	last = cmd_head;
	while (last)
	{
		if (last -> next == NULL)
			return (last);
		last = last -> next;
	}
	return (0);
}

/**
 * @brief Finish up last cmd in cmd_list.
 * 
 * @param new 		Last cmd.
 * @param cmd_head 	List of cmds.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_finish_cmd_list(t_cmd *new, t_cmd **cmd_head)
{
	if (new->arg_buf)
	{
		new->args = ft_split(new->arg_buf, ' ');
		if (!new->args)
			return (ERR_MALLOC);
	}
	if (new->delim_buf)
	{
		new->delims = ft_split(new->delim_buf, ' ');
		if (!new->delims)
			return (ERR_MALLOC);
	}
	ft_add_cmd(new, cmd_head);
	return (SUCCESS);
}
