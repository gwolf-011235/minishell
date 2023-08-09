/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/09 18:39:31 by gwolf            ###   ########.fr       */
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
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_hashtable *env_table)
{
	t_tkn_list	*tmp;
	t_err		err;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPEND)
			err = ft_handle_redirect(&tmp, env_table);
		else if (tmp->type == HEREDOC)
			err = ft_handle_heredoc(&tmp);
		else if (tmp->type == ASSIGN)
			err = ft_handle_assign(&tmp, env_table);
		else if (tmp->type == PIPE || tmp->type == NEW_LINE)
			err = SUCCESS;
		else
			err = ft_handle_arg(&tmp, env_table);
		if (err != SUCCESS)
			return (err);
		if (tmp == NULL || tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	*head = ft_list_first(tmp);
	ft_del_target_type(head, DELETE);
	return (SUCCESS);
}

t_err	ft_handle_heredoc(t_tkn_list **list)
{
	t_track	input;
	t_err	err;

	*list = (*list)->next;
	ft_init_tracker(&input, (*list)->content);
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '\'' && !input.quoted)
			err = ft_rm_single_quote(&input);
		else if (input.str[input.pos] == '"')
			err = ft_rm_double_quote(&input);
		else
			err = ft_move_tracker(&input);
		if (err != SUCCESS)
			return (err);
	}
	return (err);
}

t_err	ft_handle_redirect(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	*list = (*list)->next;
	ft_init_tracker(&input, (*list)->content);
	err = ft_expander_full(&input, symtab);
	if (err != SUCCESS)
		return (err);
	(*list)->content = input.str;
	if ((*list)->content[0] == '\0' && !input.found_quote)
		(*list)->prev->type = AMBIGUOUS;
	return (err);
}

t_err	ft_handle_assign(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*list)->content);
	err = ft_expander_full(&input, symtab);
	if (err != SUCCESS)
		return (err);
	(*list)->content = input.str;
	(*list)->type = ARG;
	return (err);
}

t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*list)->content);
	while (input.str[input.pos])
	{
		err = ft_expander_arg(&input, symtab);
		if (err != SUCCESS)
			return (err);
		(*list)->content = input.str;
		if (input.last_expand_len > 0 && !input.quoted && input.expanded)
		{
			err = ft_field_split(&input, list);
			if (err != SUCCESS && err != ERR_NOSPLIT)
				return (err);
			if (err == SUCCESS)
				ft_init_tracker(&input, (*list)->content);
		}
	}
	if (ft_strlen((*list)->content) == 0 && !input.found_quote)
		(*list)->type = DELETE;
	return (err);
}
