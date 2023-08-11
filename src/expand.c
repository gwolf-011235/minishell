/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/11 16:05:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand.c
 * @brief Functions to exec different expansions depending on token type.
 */
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
			err = ft_expand_redirect(&tmp, env_table);
		else if (tmp->type == HEREDOC)
			err = ft_expand_heredoc(&tmp);
		else if (tmp->type == ASSIGN)
			err = ft_expand_assign(&tmp, env_table);
		else if (tmp->type == PIPE || tmp->type == NEWL)
			err = SUCCESS;
		else
			err = ft_expand_arg(&tmp, env_table);
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

/**
 * @brief Expands token after HEREDOC = delim.
 *
 * Move forward a node.
 * Init tracker with ft_init_tracker().
 * Removes quotes of heredoc delim.
 * @param list Pointer to HEREDOC node.
 * @return t_err SUCCESS
 */
t_err	ft_expand_heredoc(t_tkn_list **list)
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

/**
 * @brief Expands token after REDIRECT = Infile, Outfile
 *
 * Move forward a node.
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with ft_expander_full().
 * If expanded token is nothing and was not quoted, change type of the
 * redirect node (previous one) to AMBIGUOUS.
 * @param list Pointer to REDIRECT node.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_redirect(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	*list = (*list)->next;
	ft_init_tracker(&input, (*list)->content);
	err = ft_expander_arg(&input, symtab, INFILE);
	if (err != SUCCESS)
		return (err);
	(*list)->content = input.str;
	if ((*list)->content[0] == '\0' && !input.found_quote)
		(*list)->prev->type = AMBIGUOUS;
	return (err);
}

/**
 * @brief Expands ASSIGN token.
 *
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with ft_expander_full().
 * Set type to ARG to not coonfuse parser.
 * @param list Pointer to ASSIGN node.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_assign(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*list)->content);
	err = ft_expander_arg(&input, symtab, ASSIGN);
	if (err != SUCCESS)
		return (err);
	(*list)->content = input.str;
	(*list)->type = ARG;
	return (err);
}

/**
 * @brief Expands ARG token.
 *
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with special ft_expander_arg().
 * If expansion on unquoted var: check with ft_field_split() if node
 * has to be split. If ft_field_split() fires it resets the tracker to the last
 * node of the split to continue expansion.
 * If expanded node is empty, and was no quotes found mark it as DELETE.
 * @param list Pointer to ARG token.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_arg(t_tkn_list **list, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*list)->content);
	while (input.str[input.pos])
	{
		err = ft_expander_arg(&input, symtab, ARG);
		if (err != SUCCESS)
			return (err);
		(*list)->content = input.str;
		if (input.last_expand_len > 0 && !input.quoted)
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
