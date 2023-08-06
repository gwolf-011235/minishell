/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:19:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 18:24:06 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

t_err	ft_init_tracker(t_track *input, char *str)
{
	input->str = str;
	input->pos = 0;
	return (SUCCESS);
}

t_err	ft_move_tracker(t_track *input)
{
	input->pos++;
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