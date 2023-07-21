/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 16:08:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand.c
 * @brief Contains driver function to handle expansion and quote removal.
 */
#include "mod_expand.h"

/**
 * @brief Search for token in input string and replace with replace.
 *
 * @param input String.
 * @param pos Current position.
 * @param token Struct containing the searched for token.
 * @param replace Struct containing the replacement.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace)
{
	size_t	new_len;
	char	*new_str;
	char	*old_str;
	size_t	cur_pos;

	new_len = ft_strlen(input->str) - token.len + replace.len;
	new_str = malloc(new_len);
	if (!new_str)
		return (ERR_MALLOC);
	*new_str = '\0';
	old_str = input->str;
	cur_pos = input->pos;
	ft_strncat(new_str, old_str, cur_pos);
	ft_strcat(new_str, replace.ptr);
	cur_pos += token.len;
	ft_strcat(new_str, (old_str + cur_pos));
	free(old_str);
	input->str = new_str;
	return (SUCCESS);
}

/**
 * @brief Remove single char from string. Doesn't realloc.
 *
 * @param input String.
 * @param pos Current position.
 * @return t_err SUCCESS
 */
t_err	ft_eat_char(char *input, size_t pos)
{
	char	*str1;
	char	*str2;

	str1 = input + pos;
	str2 = str1 + 1;
	while (*str1)
		*str1++ = *str2++;
	return (SUCCESS);
}

/**
 * @brief Handle single quotes.
 *
 * Remove found single quote with ft_eat_char().
 * Jump over quoted part, searching for the second single.
 * Remove the second single quote.
 *
 * @param expr String
 * @param pos Current position
 * @return t_err SUCCESS
 */
t_err	ft_handle_single_quote(t_track *input)
{
	ft_eat_char(input->str, input->pos);
	while (input->str[input->pos] != '\'')
		input->pos++;
	ft_eat_char(input->str, input->pos);
	return (SUCCESS);
}

/**
 * @brief Handle double quotes.
 *
 * Remove found double quote with ft_eat_char().
 * Switch bool in_quotes on/off.
 * This way we know if we are in double quotes or not.
 * The next time we see a double quote the switch gets flipped again.
 *
 * @param expr String.
 * @param pos Current position.
 * @param in_double_quotes Pointer to change switch.
 * @return t_err SUCCESS.
 */
t_err	ft_handle_double_quote(t_track *input, bool *in_double_quotes)
{
	ft_eat_char(input->str, input->pos);
	*in_double_quotes = !(*in_double_quotes);
	return (SUCCESS);
}

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
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info)
{
	t_track	input;
	bool	in_double_quotes;
	t_err	err;

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
