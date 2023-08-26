/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 13:25:06 by gwolf            ###   ########.fr       */
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
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_hashtable *env_table, t_buf *buf)
{
	t_tkn_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_expand_router(&tmp, tmp->type, env_table, buf) == ERR_MALLOC)
			return (ft_expand_err(head));
		*head = ft_list_first(tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	ft_del_target_type(head, DELETE);
	return (SUCCESS);
}

t_err	ft_expand_router(t_tkn_list **tmp, t_type type, t_hashtable *env_table, t_buf *buf)
{
	t_err	err;

	if (type == INFILE || type == OUTFILE || type == APPEND)
		err = ft_expand_redirect(tmp, env_table);
	else if (type == HEREDOC)
		err = ft_expand_heredoc(tmp);
	else if (type == ASSIGN)
		err = ft_expand_assign(tmp, env_table);
	else if (type == PIPE || type == NEWL)
		err = SUCCESS;
	else
		err = ft_expand_arg(tmp, env_table, buf);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief	Handle ERR_MALLOC in expand.
 *
 * Clears token list.
 * Return err message.
 * @param lst_head		Head of token list.
 * @return t_err		ERR_EXPANDER
 */
t_err	ft_expand_err(t_tkn_list **lst_head)
{
	g_status = 1;
	ft_free_lst(lst_head);
	return (ft_print_error(ERR_EXPANDER));
}

