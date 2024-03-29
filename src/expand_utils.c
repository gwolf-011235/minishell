/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:19:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/28 09:59:56 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_utils.c
 * @brief Functions for tracker and creating a new string with replacement.
 */
#include "mod_expand.h"

/**
 * @brief Initialize a tracker
 *
 * @param input Pointer to tracker.
 * @param str String which shall be tracked.
 */
void	ft_init_tracker(t_track *input, char *str, t_type type)
{
	input->str = str;
	input->pos = 0;
	input->quoted = false;
	input->last_expand_len = 0;
	input->found_quote = false;
	input->type = type;
}

/**
 * @brief Move tracker forward by one.
 *
 * @param input Pointer to tracker.
 * @return t_err SUCCESS
 */
t_err	ft_move_tracker(t_track *input)
{
	input->pos++;
	return (SUCCESS);
}

/**
 * @brief Remove single char from string. Doesn't realloc.
 *
 * @param input Pointer to tracker.
 */
void	ft_eat_char(t_track *input)
{
	char	*str1;
	char	*str2;

	str1 = input->str + input->pos;
	str2 = str1 + 1;
	while (*str1)
		*str1++ = *str2++;
}

/**
 * @brief Search for token in input string and replace with replace.
 *
 * Calc len of the new string.
 * Copy everything until token starts.
 * Copy replacement string.
 * Copy everything after token ends.
 * @param input Pointer to tracker.
 * @param token Struct containing searched for token.
 * @param replace Struct containing replacement.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace)
{
	size_t	new_len;
	char	*new_str;
	char	*old_str;
	size_t	cur_pos;

	new_len = ft_strlen(input->str) - token.len + replace.len + 1;
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
 * @brief Trims a tracked string of spaces.
 *
 * If after expansion only 1 word remains, it can save be trimmed of spaces.
 * @param input Tracked string
 * @return t_err ERR_NOSPLIT
 */
t_err	ft_trim_single_word(t_track *input)
{
	size_t	last_expand;

	input->pos = input->pos - input->last_expand_len;
	last_expand = input->last_expand_len;
	while (last_expand--)
	{
		if (ft_isspace(input->str[input->pos]))
			ft_eat_char(input);
		else
			ft_move_tracker(input);
	}
	return (ERR_NOSPLIT);
}
