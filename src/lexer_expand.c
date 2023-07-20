/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:01:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/20 09:08:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_expand.h"

/**
 * @brief Loop through token list and expand content.
 *
 * If a heredoc token is encountered, jump over the token and the next one.
 * Else pass the token content to ft_expand_expr() which handles expansion.
 *
 * @param list List of tokens.
 * @param data Overarching struct.
 * @return t_error SUCCESS, ERR_MALLOC.
 */
t_error	ft_expand_tkn_lst(t_tkn_list *list, t_data *data)
{
	t_error	err;

	while (list)
	{
		if (!ft_strncmp(list->content, "<<", ft_strlen(list->content)))
			list = list->next->next;
		else
		{
			err = ft_expand_expr(&list->content, data->env_table, &data->info);
			if (err != SUCCESS)
				return (err);
			list = list->next;
		}
	}
	return (SUCCESS);
}
