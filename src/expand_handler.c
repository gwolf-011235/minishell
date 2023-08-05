/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 11:31:37 by gwolf            ###   ########.fr       */
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
	if (err != SUCCESS)
		return (err);
	err = ft_quote_removal(input);
	return (err);
}

t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;
	bool	exec;

	*list = (*list)->next;
	input.str = (*list)->content;
	input.pos = 0;
	exec = false;
	err = ft_expander(&input, symtab, &exec);
	if (err != SUCCESS)
		return (err);
	if (exec)
		err = ft_field_split(list);
	err = ft_quote_removal(input);
	return (err);
}