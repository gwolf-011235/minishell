/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/07 21:46:52 by gwolf            ###   ########.fr       */
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
			err = ft_handle_redirect(&tmp, env_table);
		else
			err = ft_handle_arg(&tmp, env_table);
		if (err != SUCCESS)
			return (err);
		if (tmp == NULL || tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	*head = ft_list_first(tmp);
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
		if (words && (*list)->next != NULL)
			*list = (*list)->next;
	}
	return (err);
}
