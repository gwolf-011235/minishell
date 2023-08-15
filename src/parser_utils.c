/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:15:09 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/15 16:22:59 by gwolf            ###   ########.fr       */
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
 * @param count_out 	Outfile counter.
 * @return t_err 		SUCCESS
 */
t_err	ft_count_str(t_tkn_list *lst, int *count_arg, int *count_delim,
			int *count_out)
{
	while (lst)
	{
		if (lst->type == HEREDOC || lst->type == QUOTEDOC)
		{
			lst = lst->next;
			(*count_delim)++;
		}
		else if (lst->type == PIPE)
			return (SUCCESS);
		else if (lst->type == INFILE)
			lst = lst->next;
		else if (lst->type == OUTFILE || lst->type == APPEND)
		{
			lst = lst->next;
			(*count_out)++;
		}
		else if (lst->type == NEWL)
			;
		else if (lst->type == ARG)
			(*count_arg)++;
		lst = lst->next;
	}
	return (SUCCESS);
}

/**
 * @brief Reserve memory space for argument and/or delimiter
 * and/or outfiles string array.
 *
 * @param new 			New cmd struct to be created.
 * @param count_arg 	Amount of arguments.
 * @param count_delim 	Amount of delimiters.
 * @param count_out 	Amount of outfiles.
 * @return t_err 		ERR_MALLOC, SUCCESS
 */
t_err	ft_create_str_arr(t_cmd *tmp, int count_arg, int count_delim,
			int count_out)
{
	t_err	err;

	err = SUCCESS;
	if (count_arg && err == SUCCESS)
		err = ft_malloc_arr(&tmp->args, NULL, count_arg);
	if (count_delim && err == SUCCESS)
		err = ft_malloc_arr(&tmp->delims, &tmp->hdoc_quoted, count_delim);
	if (count_out && err == SUCCESS)
		err = ft_malloc_arr(&tmp->outfiles, &tmp->append_switches, count_out);
	return (err);
}

/**
 * @brief Malloc string array and if required boolean array.
 *
 * @param str 		Address of string array.
 * @param b_arr 	Adress of boolean array.
 * @param count 	Size of array.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_malloc_arr(char ***str, bool **b_arr, int count)
{
	*str = malloc(sizeof(char *) * (count + 1));
	if (!*str)
		return (ERR_MALLOC);
	(*str)[count] = NULL;
	if (b_arr)
	{
		*b_arr = malloc(sizeof(bool) * count);
		if (!*b_arr)
			return (ERR_MALLOC);
	}
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
	tmp->out_pos = 0;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->fd_pipe[0] = -1;
	tmp->fd_pipe[1] = -1;
	tmp->fd_prev_pipe[0] = -1;
	tmp->fd_prev_pipe[1] = -1;
	tmp->infile = false;
	tmp->outfile = false;
	tmp->index = -1;
	tmp->cmd_num = 0;
	tmp->heredoc = NULL;
	tmp->args = NULL;
	tmp->delims = NULL;
	tmp->outfiles = NULL;
	tmp->append_switches = NULL;
	tmp->next = NULL;
}
