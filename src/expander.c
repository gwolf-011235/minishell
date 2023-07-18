/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/18 02:04:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expander.c
 * @brief Driver function for expansion and quote removal of token list.
 */
#include "expander.h"

/**
 * @brief Expand expressions received from token list.
 *
 * Go through the string and check for special chars.
 * Tilde: ft_expand_tilde().
 * $: ft_expand_var().
 * Single quote: ft_handle_single_quote().
 * Double quote: ft_handle_double_quote().
 *
 * @param expr The expression to be expanded.
 * @param symtab The environment table
 * @param info Data for return code and shell name.
 * @return t_error SUCCESS, ERR_MALLOC
 */
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info)
{
	t_track	input;
	bool	in_double_quotes;
	t_error	err;

	input.str = *expr;
	input.pos = 0;
	in_double_quotes = false;
	err = SUCCESS;
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '\'' && !in_double_quotes)
			ft_handle_single_quote(&input);
		else if (input.str[input.pos] == '"')
			ft_handle_double_quote(&input, &in_double_quotes);
		else if (input.str[input.pos] == '~' && !in_double_quotes)
			err = ft_expand_tilde(&input, symtab);
		else if (input.str[input.pos] == '$')
			err = ft_expand_var(&input, symtab, info, in_double_quotes);
		else
			input.pos++;
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	*expr = input.str;
	return (SUCCESS);
}

/**
 * @brief Loop through token list and expand content.
 *
 * If a redirect token is encountered, check if the next is also one.
 * If yes jump over the redirect and the next token - which would be
 * the name of the heredoc.
 * Pass the token content to ft_expand_expr() which handles expansion.
 *
 * @param list List of tokens.
 * @param data Overarching struct.
 * @return t_error SUCCESS, ERR_MALLOC.
 */
t_error	ft_expand_tkn_lst(t_tkn_list *list, t_data *data)
{
	t_error	err;

	while (list)
	{
		if (list->content[0] == '<' && list->next->content[0] == '<')
			list = list->next->next->next;
		err = ft_expand_expr(&list->content, data->env_table, &data->info);
		if (err != SUCCESS)
			return (err);
		list = list->next;
	}
	return (SUCCESS);
}
