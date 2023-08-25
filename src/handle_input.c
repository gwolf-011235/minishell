/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:12 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/25 16:30:01 by gwolf            ###   ########.fr       */
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
void	ft_handle_input(char *input, t_data *data)
{
	t_tkn_list	*lst;
	t_err		err;
	t_cmd		*cmd;

	lst = NULL;
	cmd = NULL;
	if (ft_check_syntax(input) == ERR_SYNTAX)
		return ;
	err = ft_lex_input(&lst, input, &data->buf);
	if (err != SUCCESS)
		return ;
	err = ft_expand_tkn_lst(&lst, data->env_table, &data->buf);
	if (err != SUCCESS)
	{
		ft_free_lst(&lst);
		return ;
	}
	err = ft_parser(lst, &cmd);
	if (err != SUCCESS)
		return ;
	ft_free_lst(&lst);
	err = ft_executor(cmd, data);
	ft_cleanup_cmd_list(cmd);
	return ;
}
