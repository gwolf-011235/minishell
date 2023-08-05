/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 20:13:19 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

t_err	ft_handle_heredoc(t_tkn_list **list)
{
	t_track	input;
	t_err	err;

	*list = (*list)->next;
	input.str = (*list)->content;
	input.pos = 0;
	err = ft_quote_removal(input);
	return (err);
}

t_err	ft_handle_redirect(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;
	bool	exec;

	*list = (*list)->next;
	input.str = (*list)->content;
	input.pos = 0;
	exec = false;
	err = ft_expander(&input, symtab, &exec);
	(*list)->content = input.str;
	input.pos = 0;
	if (err != SUCCESS)
		return (err);
	if (input.str[input.pos] == '\0')
		(*list)->prev->type = AMBIGUOUS;
	else
		err = ft_quote_removal(input);
	return (err);
}

t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;
	bool	exec;
	size_t	words;

	*list = (*list)->next;
	input.str = (*list)->content;
	input.pos = 0;
	exec = false;
	err = ft_expander(&input, symtab, &exec);
	(*list)->content = input.str;
	input.pos = 0;
	if (err != SUCCESS)
		return (err);
	if (exec)
	{
		words = 0;
		err = ft_field_split(list, &words);
		if (err != SUCCESS)
			return (err);
	}
	err = ft_quote_removal(input);
	return (err);
}
