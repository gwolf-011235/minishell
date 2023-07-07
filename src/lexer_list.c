/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 20:21:32 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_list.h"

t_error	ft_list_token(t_data *data, char *input)
{
	t_src		src;
	t_tok		token;
	t_error		err;
	t_tkn_list	*new;
	t_tkn_list	*prev;

	src.buf = input;
	src.buf_size = ft_strlen(input);
	src.cur_pos = INIT_SRC_POS;
	prev = data->lst_head;
	err = ft_tokenise(&src, &token);
	while (err != EOF)
	{
		err = ft_new_node(new, &prev, token.tok);
		if (err != SUCCESS)
		{
			ft_free_list(data->lst_head);
			ft_free_tok(&token);
			return (err);
		}
		ft_lstadd_back(&data->lst_head, new);
		prev = new;
		ft_free_tok(&token);
		free(new);
		err = ft_tokenise(&src, &token);
	}
	return (SUCCESS);
}

t_error	ft_new_node(t_tkn_list *new, t_tkn_list **prev, char *s)
{
	new = malloc (sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->tkn_str = s;
	new->next = NULL;
	if (*prev)
		new->prev = *prev;
	else
		*prev = new;
	return (SUCCESS);
}
