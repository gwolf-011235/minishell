/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:05:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 10:42:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_types.c
 * @brief Functions to exec different expansions depending on token type.
 */
#include "mod_expand.h"

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
	char	*tmp;

	*node = (*node)->next;
	ft_init_tracker(&input, (*node)->content, INFILE);
	tmp = NULL;
	if (ft_err_strdup(input.str, &tmp, "minishell: malloc") == ERR_MALLOC)
		return (ERR_MALLOC);
	if (ft_expander(&input, symtab, input.type) == ERR_MALLOC)
		return (ERR_MALLOC);
	(*node)->content = input.str;
	if ((*node)->content[0] == '\0' && !input.found_quote)
	{
		ft_print_warning(ERR_AMBIGUOUS, tmp);
		(*node)->prev->type = AMBIGUOUS;
	}
	free (tmp);
	return (SUCCESS);
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

	ft_init_tracker(&input, (*node)->content, ASSIGN);
	if (ft_expander(&input, symtab, input.type) == ERR_MALLOC)
		return (ERR_MALLOC);
	(*node)->content = input.str;
	(*node)->type = ARG;
	return (SUCCESS);
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
t_err	ft_expand_arg(t_tkn_list **node, t_hashtable *symtab, t_buf *buf)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, (*node)->content, ARG);
	while (input.str[input.pos])
	{
		if (ft_expander(&input, symtab, input.type) == ERR_MALLOC)
			return (ERR_MALLOC);
		(*node)->content = input.str;
		if (input.last_expand_len > 0 && !input.quoted)
		{
			err = ft_field_split(&input, node, buf);
			if (err == ERR_MALLOC)
				return (err);
			if (err == SUCCESS)
				ft_init_tracker(&input, (*node)->content, ARG);
		}
	}
	if (ft_strlen((*node)->content) == 0 && !input.found_quote)
		(*node)->type = DELETE;
	return (SUCCESS);
}
