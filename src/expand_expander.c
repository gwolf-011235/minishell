/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/07 22:21:14 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand.c
 * @brief Contains driver function to handle expansion and quote removal.
 */
#include "mod_expand.h"

t_err	ft_expander_redirect(t_track *input, t_hashtable *symtab)
{
	t_err	err;

	while (input->str[input->pos])
	{
		if (input->str[input->pos] == '\'' && !input->quoted)
			err = ft_rm_single_quote(input);
		else if (input->str[input->pos] == '"')
			err = ft_rm_double_quote(input);
		else if (input->str[input->pos] == '~' && !input->quoted)
			err = ft_expand_tilde(input, symtab);
		else if (input->str[input->pos] == '$')
			err = ft_expand_var(input, symtab);
		else
			err = ft_move_tracker(input);
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	return (SUCCESS);
}

/**
 * @brief Expand expressions received from token list.
 *
 * Go through the string and check for special chars.
 * Tilde: ft_expand_tilde().
 * $: ft_expand_var().
 * Single quote: ft_skip_single_quote().
 * Double quote: ft_skip_double_quote().
 *
 * @param expr The expression to be expanded.
 * @param symtab The environment table
 * @param info Data for return code and shell name.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expander(char **str, t_hashtable *symtab)
{
	t_track	input;
	bool	in_double_quotes;
	t_err	err;

	ft_init_tracker(&input, *str);
	in_double_quotes = false;
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '\'' && !in_double_quotes)
			err = ft_skip_single_quote(&input);
		else if (input.str[input.pos] == '"')
			err = ft_skip_double_quote(&input, &in_double_quotes);
		else if (input.str[input.pos] == '~' && !in_double_quotes)
			err = ft_expand_tilde(&input, symtab);
		else if (input.str[input.pos] == '$')
			err = ft_expand_var(&input, symtab);
		else
			err = ft_move_tracker(&input);
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	*str = input.str;
	return (SUCCESS);
}

/**
 * @brief Skip single quotes.
 *
 * Skip found single quote.
 * Jump over quoted part, searching for the second single.
 * Skip second single quote.
 *
 * @param expr String
 * @param pos Current position
 * @return t_err SUCCESS
 */
t_err	ft_skip_single_quote(t_track *input)
{
	input->pos++;
	while (input->str[input->pos] != '\'')
		input->pos++;
	input->pos++;
	return (SUCCESS);
}

/**
 * @brief Skip double quotes.
 *
 * Skip found double quote.
 * Switch bool in_quotes on/off.
 * This way we know if we are in double quotes or not.
 * The next time we see a double quote the switch gets flipped again.
 *
 * @param expr String.
 * @param pos Current position.
 * @param in_double_quotes Pointer to change switch.
 * @return t_err SUCCESS.
 */
t_err	ft_skip_double_quote(t_track *input, bool *in_double_quotes)
{
	input->pos++;
	*in_double_quotes = !(*in_double_quotes);
	return (SUCCESS);
}
