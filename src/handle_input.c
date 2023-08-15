/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:12 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/14 13:05:47 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_input.c
 * @brief Driver function for input handling.
 */

#include "mod_handle_input.h"

/**
 * @brief Driver function process input.
 * 
 * Input is checked for syntax errors.
 * Input is lexed, splitted into tokens which are saved
 * in a token list.
 * Token list is iterated and expanded if necessary.
 * The expanded token list is parsed and the content categorised into
 * a list of cmds.
 * The list of cmds is processed by the executor.
 * @param input 	Input string.
 * @param data 		Overarching data struct containing the env.
 * @return t_err 	ERR_EMPTY, ERR_MALLOC, ERR_SYNTAX,  ERR_PIPE, SUCCESS
 */
t_err	ft_handle_input(char *input, t_data *data)
{
	t_tkn_list	*lst;
	t_err		err;
	t_cmd		*cmd;

	lst = NULL;
	cmd = NULL;
	err = ft_check_syntax(input);
	if (err != SUCCESS)
		return (err);
	err = ft_lex_input(&lst, input);
	if (err != SUCCESS)
		return (err);
	err = ft_expand_tkn_lst(&lst, data->env_table);
	if (err != SUCCESS)
		return (err);
	err = ft_parser(lst, &cmd);
	if (err != SUCCESS)
		return (err);
	ft_free_lst(&lst);
	err = ft_executor(cmd, data);
	if (err != SUCCESS)
		ft_cleanup_cmd_list(cmd);
	return (SUCCESS);
}
