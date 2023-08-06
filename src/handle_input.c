/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:12 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/06 18:49:48 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_input.c
 * @brief Driver function for input handling.
 */

#include "mod_handle_input.h"

t_err	ft_handle_input(char *input, t_data *data)
{
	t_tkn_list	*lst;
	t_err		err;
	//t_cmd		*cmd;

	lst = NULL;
	err = ft_check_syntax(input);
	if (err != SUCCESS)
		return (err);
	err = ft_lex_input(&lst, input);
	if (err != SUCCESS)
		return (err);
	err = ft_expand_tkn_lst(&lst, data->env_table);
	if (err != SUCCESS)
		return (err);
	//err = ft_parser(lst, &cmd);
	if (err != SUCCESS)
		return (err);
	ft_free_lst(&lst);
	/* err = ft_executor(cmd);
	if (err != SUCCESS)
		return (err); */
	return (SUCCESS);
}
