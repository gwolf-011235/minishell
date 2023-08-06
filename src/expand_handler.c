/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 13:28:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

t_err	ft_handle_heredoc(t_tkn_list **list)
{
	t_err	err;

	*list = (*list)->next;
	err = ft_quote_removal((*list)->content);
	return (err);
}

t_err	ft_handle_redirect(t_tkn_list **list, t_hashtable *symtab)
{
	bool	exec;
	t_err	err;

	*list = (*list)->next;
	exec = false;
	err = ft_expander(&((*list)->content), symtab, &exec);
	if (err != SUCCESS)
		return (err);
	if ((*list)->content && (*list)->content[0] == '\0')
		(*list)->prev->type = AMBIGUOUS;
	else
		err = ft_quote_removal((*list)->content);
	return (err);
}

t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab)
{
	bool	exec;
	size_t	words;
	t_err	err;

	exec = false;
	words = 1;
	err = ft_expander(&((*list)->content), symtab, &exec);
	if (err != SUCCESS)
		return (err);
	if (exec)
	{
		words = 0;
		err = ft_field_split(list, &words);
		if (err != SUCCESS)
			return (err);
	}
	while (words-- && *list)
	{
		err = ft_quote_removal((*list)->content);
		*list = (*list)->next;
	}
	return (err);
}
