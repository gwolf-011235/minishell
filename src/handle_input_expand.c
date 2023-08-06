/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:01:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 13:26:36 by gwolf            ###   ########.fr       */
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

t_err	ft_expand_tkn_lst(t_tkn_list **head, t_data *data)
{
	t_tkn_list	*tmp;
	t_type		type;
	t_err		err;

	tmp = *head;
	while (tmp)
	{
		type = tmp->type;
		if (type == PIPE || type == NEW_LINE)
			err = SUCCESS;
		else if (type == HEREDOC)
			err = ft_handle_heredoc(&tmp);
		else if (type == INFILE || type == OUTFILE || type == APPEND)
			err = ft_handle_redirect(&tmp, data->env_table);
		else
			err = ft_handle_arg(&tmp, data->env_table);
		if (err != SUCCESS)
			return (err);
		if (tmp  == NULL || tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	*head = ft_list_first(tmp);
	return (SUCCESS);
}
