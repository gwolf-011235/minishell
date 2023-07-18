/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:56:07 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/18 02:05:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_utils.c
 * @brief Functions to finish expansion and quote removal.
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
t_error	ft_insert_replace(t_track *input, t_str token, t_str replace)
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
 * @return t_error SUCCESS
 */
t_error	ft_eat_char(char *input, size_t pos)
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
 * @return t_error SUCCESS
 */
t_error	ft_handle_single_quote(t_track *input)
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
 * @return t_error SUCCESS.
 */
t_error	ft_handle_double_quote(t_track *input, bool *in_double_quotes)
{
	ft_eat_char(input->str, input->pos);
	*in_double_quotes = !(*in_double_quotes);
	return (SUCCESS);
}