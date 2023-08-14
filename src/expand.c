/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/14 21:19:56 by gwolf            ###   ########.fr       */
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
 * Depending on type of token perform expansions:
 * Redirect: tilde and dollar expand, quote removal, flag if AMBIGUOUS.
 * Heredoc: quote removal.
 * Assign: tilde after = and dollar expand, quote removal, set type to ARG.
 * Arg: tilde and dollar expand, field split, quote removal, flag if DELETE.
 * Loop through with tmp. Since the list itself can change (new nodes added after
 * field split) the head pointer needs to be updated after loop.
 * At the end deletes all nodes of type DELETE.
 * @param head Pointer pointer to head of list.
 * @param env_table Environment.
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
		if (tmp->next == NULL)
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
 * Remove quotes of heredoc delim.
 * If quotes were found in delim, set type prev node to QUOTEDOC.
 * @param node Pointer to HEREDOC node.
 * @return t_err SUCCESS
 */
t_err	ft_expand_heredoc(t_tkn_list **node)
{
	t_track	input;

	*node = (*node)->next;
	ft_init_tracker(&input, (*node)->content, HEREDOC);
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '\'' && !input.quoted)
			ft_rm_single_quote(&input);
		else if (input.str[input.pos] == '"')
			ft_rm_double_quote(&input);
		else
			ft_move_tracker(&input);
	}
	if (input.found_quote)
		(*node)->prev->type = QUOTEDOC;
	return (SUCCESS);
}

/**
 * @brief Expands token after REDIRECT = Infile, Outfile
 *
 * Move forward a node.
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with ft_expander().
 * If expanded token is empty and was not quoted, change type of previous node
 * (containing redirect symbol) to AMBIGUOUS.
 * @param node Pointer to REDIRECT node.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_redirect(t_tkn_list **node, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	*node = (*node)->next;
	ft_init_tracker(&input, (*node)->content, INFILE);
	err = ft_expander(&input, symtab, input.type);
	if (err != SUCCESS)
		return (err);
	(*node)->content = input.str;
	if ((*node)->content[0] == '\0' && !input.found_quote)
		(*node)->prev->type = AMBIGUOUS;
	return (err);
}

/**
 * @brief Expands ASSIGN token.
 *
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with ft_expander().
 * Set type to ARG to not coonfuse parser.
 * @param list Pointer to ASSIGN node.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_assign(t_tkn_list **node, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*node)->content, ASSIGN);
	err = ft_expander(&input, symtab, input.type);
	if (err != SUCCESS)
		return (err);
	(*node)->content = input.str;
	(*node)->type = ARG;
	return (err);
}

/**
 * @brief Expands ARG token.
 *
 * Init tracker with ft_init_tracker().
 * Expand and quote removal with ft_expander().
 * If expansion on unquoted dollar: check with ft_field_split() if node
 * has to be split. If ft_field_split() fires it resets the tracker to the last
 * node of the split to continue expansion.
 * If expanded node is empty, and no quotes found set type to DELETE.
 * @param node Pointer to ARG token.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_arg(t_tkn_list **node, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*node)->content, ARG);
	while (input.str[input.pos])
	{
		err = ft_expander(&input, symtab, input.type);
		if (err != SUCCESS)
			return (err);
		(*node)->content = input.str;
		if (input.last_expand_len > 0 && !input.quoted)
		{
			err = ft_field_split(&input, node);
			if (err != SUCCESS && err != ERR_NOSPLIT)
				return (err);
			if (err == SUCCESS)
				ft_init_tracker(&input, (*node)->content, ARG);
		}
	}
	if (ft_strlen((*node)->content) == 0 && !input.found_quote)
		(*node)->type = DELETE;
	return (SUCCESS);
}
