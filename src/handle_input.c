/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:12 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/07 12:32:42 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file handle_input.c
 * @brief Driver function for input handling.
 */

#include "mod_handle_input.h"

t_err	ft_handle_input(char *input, t_data *data, char **envp)
{
	t_tkn_list	*lst;
	t_err		err;
	t_cmd		*cmd;

	lst = NULL;
	err = ft_check_syntax(input);
	if (err != SUCCESS)
		return (err);
	err = ft_lex_input(&lst, input);
	if (err != SUCCESS)
		return (err);
	err = ft_expand_tkn_lst(lst, data);
	if (err != SUCCESS)
		return (err);
	err = ft_parser(lst, &cmd);
	if (err != SUCCESS)
		return (err);
	ft_free_lst(&lst);
	err = ft_executor(cmd, envp);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
