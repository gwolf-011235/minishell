/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/14 20:29:53 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand.c
 * @brief Contains driver function to handle expansion and quote removal.
 */
#include "mod_expand.h"

/**
 * @brief Expand input received from token list.
 *
 * Loop through string using tracker and check for special chars.
 * Single quote: ft_skip_single_quote().
 * Double quote: ft_skip_double_quote().
 * Tilde: ft_expand_tilde().
 * $: ft_expand_dollar().
 * Uses passed type to activate different functionalities:
 * If type == ASSIGN additional tilde expand is checked:
 * Tilde is only expanded at pos == 0. But ASSIGN expands tilde also if it is
 * directly after the first '='. For this the complicated if condition checks
 * (1) if type is ASSIGN
 * (2) pos of first '=' found (which has to be after the var name, else it
 * wouldn't be an ASSIGN) equals tilde pos -1.
 * If type == ARG a break out of loop happens if the expansion wasn't quoted.
 * This makes it possible to field split the expanded part.
 * To ensure this works properly last_expanded_len is set to 0 every loop.
 * @param input Pointer to tracker.
 * @param symtab The environment table
 * @param type Type of the expanded node.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expander_arg(t_track *input, t_hashtable *symtab, t_type type)
{
	t_err	err;

	while (input->str[input->pos])
	{
		input->last_expand_len = 0;
		if (input->str[input->pos] == '\'' && !input->quoted)
			err = ft_rm_single_quote(input);
		else if (input->str[input->pos] == '"')
			err = ft_rm_double_quote(input);
		else if (input->str[input->pos] == '~'
			&& (input->pos == 0 || (type == ASSIGN && ft_strchr(input->str, '=')
					== input->str + input->pos -1)))
			err = ft_expand_tilde(input, symtab);
		else if (input->str[input->pos] == '$')
		{
			err = ft_expand_dollar(input, symtab);
			if (type == ARG && input->last_expand_len > 0 && !input->quoted)
				break ;
		}
		else
			err = ft_move_tracker(input);
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	return (SUCCESS);
}

/**
 * @brief Remove single quotes.
 *
 * Remove found single quote with ft_eat_char().
 * Jump over quoted part, searching for the second single.
 * Remove the second single quote.
 * @param input Pointer to tracker.
 * @return t_err SUCCESS
 */
t_err	ft_rm_single_quote(t_track *input)
{
	ft_eat_char(input);
	while (input->str[input->pos] != '\'')
		input->pos++;
	ft_eat_char(input);
	input->found_quote = true;
	return (SUCCESS);
}

/**
 * @brief Remove double quotes.
 *
 * Remove found double quote with ft_eat_char().
 * Switch bool in_quotes on/off.
 * This way we know if we are in double quotes or not.
 * The next time we see a double quote the switch gets flipped again.
 * @param input Pointer to tracker.
 * @return t_err SUCCESS.
 */
t_err	ft_rm_double_quote(t_track *input)
{
	ft_eat_char(input);
	input->quoted = !(input->quoted);
	input->found_quote = true;
	return (SUCCESS);
}

t_err	ft_expander_heredoc(char *str, t_hashtable *symtab)
{
	t_track	input;
	t_err	err;

	ft_init_tracker(&input, str, HEREDOC);
	while (input.str[input.pos])
	{
		if (input.str[input.pos] == '$')
			err = ft_expand_dollar(&input, symtab);
		else
			err = ft_move_tracker(&input);
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	return (SUCCESS);
}