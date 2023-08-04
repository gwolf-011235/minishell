/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:01:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/04 19:21:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

/**
 * @brief Loop through token list and expand content.
 *
 * If a heredoc token is encountered, jump over the token and the next one.
 * Else pass the token content to ft_expand_expr() which handles expansion.
 *
 * @param list List of tokens.
 * @param data Overarching struct.
 * @return t_err SUCCESS, ERR_MALLOC.
 */

t_err	ft_expand_tkn_lst(t_tkn_list *list, t_data *data)
{
	t_err	err;
	t_type	type;

	while (list)
	{
		type = list->type;
		if (type == PIPE || type == NEWLINE)
		{
			list = list->next;
			continue ;
		}
		if (type == HEREDOC)
			err = ft_handle_heredoc(&list);
		if (type == INFILE || type == OUTFILE || type == APPEND)
			err = ft_handle_redirect(&list, data->env_table);
		else
			err = ft_handle_arg(&list, data->env_table);
		if (err != SUCCESS)
			return (err);
		list = list->next;
	}
	return (SUCCESS);
}
