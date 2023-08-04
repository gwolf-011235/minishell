/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:15:09 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/04 14:04:14 by sqiu             ###   ########.fr       */
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
 * @brief Counts the amount of arguments and, if given delimiters.
 * 
 * Arguments include the executable.
 * @param lst 			List of tokens.
 * @param count_arg 	Argument counter.
 * @param count_delim 	Delimiter counter.
 * @return t_err 		SUCCESS
 */
t_err	ft_count_str(t_tkn_list *lst, int *count_arg, int *count_delim)
{
	while (lst)
	{
		if (lst->type == HEREDOC)
		{
			lst = lst->next;
			(*count_delim)++;
		}
		else if (lst->type == PIPE)
			return (SUCCESS);
		else if (lst->type == INFILE)
			lst = lst->next;
		else if (lst->type == OUTFILE)
			lst = lst->next;
		else if (lst->type == APPEND)
			lst = lst->next;
		else if (lst->type == NWL)
			;
		else if (lst->type == ARG)
			(*count_arg)++;
		lst = lst->next;
	}
	return (SUCCESS);
}

/**
 * @brief Reserve memory space for cmd struct and in case
 * for argument and/or delimiter string arrays.
 * 
 * @param new 			New cmd struct to be created.
 * @param count_arg 	Amount of arguments.
 * @param count_delim 	Amount of delimiters.
 * @return t_err 		ERR_MALLOC, SUCCESS
 */
t_err	ft_create_str_arr(t_cmd *tmp, int count_arg, int count_delim)
{
	if (count_arg)
	{
		tmp->args = malloc(sizeof(char *) * (count_arg + 1));
		if (!tmp->args)
			return (ERR_MALLOC);
		tmp->args[count_arg] = NULL;
	}
	else
		tmp->args = NULL;
	if (count_delim)
	{
		tmp->delims = malloc(sizeof(char *) * (count_delim + 1));
		if (!tmp->delims)
			return (ERR_MALLOC);
		tmp->delims[count_delim] = NULL;
	}
	else
		tmp->delims = NULL;
	return (SUCCESS);
}

/**
 * @brief Initialise cmd values.
 * 
 * @param tmp Cmd being initialised.
 */
void	ft_init_cmd(t_cmd *tmp)
{
	tmp->arg_pos = 0;
	tmp->delim_pos = 0;
	tmp->append = 0;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->fd_pipe[0] = -1;
	tmp->fd_pipe[1] = -1;
	tmp->infile = 0;
	tmp->outfile = 0;
	tmp->index = -1;
	tmp->cmd_num = 0;
	tmp->heredoc = NULL;
	tmp->next = NULL;
}
