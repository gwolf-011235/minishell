/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/11 15:38:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand.c
 * @brief Contains driver function to handle expansion and quote removal.
 */
#include "mod_expand.h"

t_err	ft_expander_full(t_track *input, t_hashtable *symtab)
{
	t_err	err;

	while (input->str[input->pos])
	{
		if (input->str[input->pos] == '\'' && !input->quoted)
			err = ft_rm_single_quote(input);
		else if (input->str[input->pos] == '"')
			err = ft_rm_double_quote(input);
		else if (input->pos == 0 && input->str[input->pos] == '~')
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
t_err	ft_expander_arg(t_track *input, t_hashtable *symtab)
{
	t_err	err;

	while (input->str[input->pos])
	{
		input->last_expand_len= 0;
		if (input->str[input->pos] == '\'' && !input->quoted)
			err = ft_rm_single_quote(input);
		else if (input->str[input->pos] == '"')
			err = ft_rm_double_quote(input);
		else if (input->pos == 0 && input->str[input->pos] == '~')
			err = ft_expand_tilde(input, symtab);
		else if (input->str[input->pos] == '$')
		{
			err = ft_expand_var(input, symtab);
			if (input->last_expand_len > 0 && !input->quoted)
				break ;
		}
		else
			err = ft_move_tracker(input);
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	return (SUCCESS);
}
