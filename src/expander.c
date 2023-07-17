/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/17 22:19:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expander.c
 * @brief Contains driver function to handle expansion and quote removal.
 */
#include "expander.h"

/**
 * @brief Search for token in input string and replace with replace.
 *
 * @param input String.
 * @param pos Current position.
 * @param token Struct containing the searched for token.
 * @param replace Struct containing the replacement.
 * @return t_error SUCCESS, ERR_MALLOC
 */
t_error	ft_insert_replace(char **input, size_t pos, t_str_info token, t_str_info replace)
{
	size_t	new_len;
	char	*new_str;
	char	*old_str;

	new_len = ft_strlen(*input) - token.len + replace.len;
	new_str = malloc(new_len);
	if (!new_str)
		return (ERR_MALLOC);
	*new_str = '\0';
	old_str = *input;
	ft_strncat(new_str, old_str, pos);
	ft_strcat(new_str, replace.str);
	pos += token.len;
	ft_strcat(new_str, (old_str + pos));
	free(old_str);
	*input = new_str;
	return (SUCCESS);
}

/**
 * @brief Remove single char from string. Doesn't realloc.
 *
 * @param input String.
 * @param pos Current position.
 * @return t_error SUCCESS
 */
t_error	ft_eat_char(char *input, size_t pos)
{
	char	*str1;
	char	*str2;

	str1 = input + pos;
	str2 = str1 + 1;
	while (*str1)
	{
		*str1++ = *str2++;
	}
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
 * @return t_error SUCCESS
 */
t_error	ft_handle_single_quote(char *expr, size_t *pos)
{
	ft_eat_char(expr, *pos);
	while (expr[*pos] != '\'')
		(*pos)++;
	ft_eat_char(expr, *pos);
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
 * @return t_error SUCCESS.
 */
t_error	ft_handle_double_quote(char *expr, size_t pos, bool *in_double_quotes)
{
	ft_eat_char(expr, pos);
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
 * @return t_error SUCCESS, ERR_MALLOC
 */
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info)
{
	size_t	i;
	bool	in_double_quotes;
	t_error	err;

	i = 0;
	in_double_quotes = false;
	err = SUCCESS;
	while ((*expr)[i])
	{
		if ((*expr)[i] == '\'' && !in_double_quotes)
			ft_handle_single_quote(*expr, &i);
		else if ((*expr)[i] == '"')
			ft_handle_double_quote(*expr, i, &in_double_quotes);
		else if ((*expr)[i] == '~' && !in_double_quotes)
			err = ft_expand_tilde(expr, symtab, &i);
		else if ((*expr)[i] == '$')
			err = ft_expand_var(expr, symtab, &i, info);
		else
			i++;
		if (err != SUCCESS && err != ERR_NOEXPAND)
			return (err);
	}
	return (SUCCESS);
}
