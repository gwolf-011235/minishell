/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:27:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/25 17:10:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_src.c
 * @brief Contains functions to handle source string.
 */

#include "mod_lexer.h"
//#include "lexer_src.h"

/**
 * @brief Retrieves next character in source string.
 *
 * Source structure contains input string and information on its length
 * and the current position looked at.
 * @param src Source structure.
 * @param c Character looked at.
 * @return t_err SUCCESS, ERR_EOF
 */
t_err	ft_next_char(t_src *src, char *c)
{
	if (src->cur_pos == INIT_SRC_POS)
		src->cur_pos = -1;
	else
		*c = src->buf[src->cur_pos];
	if (++src->cur_pos >= src->buf_size)
		return (ERR_EOF);
	*c = src->buf[src->cur_pos];
	return (SUCCESS);
}

/**
 * @brief Go back to previous character of source string.
 *
 * @param src Source structure.
 * @return t_err ERR_OUT_OF_BOUNDS, SUCCESS
 */
t_err	ft_unget_char(t_src *src)
{
	if (src->cur_pos < 0)
		return (ERR_OUT_OF_BOUNDS);
	src->cur_pos--;
	return (SUCCESS);
}

/**
 * @brief Peek at next character.
 *
 * Look at next character in source input string w/o
 * actually changing the current position.
 * @param src Source structure.
 * @param c Character looked at.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_OUT_OF_BOUNDS
 */

t_err	ft_peek_char(t_src *src, char *c)
{
	int	peek;

	if (!src || !src->buf)
		return (ERR_EMPTY);
	peek = src->cur_pos;
	if (peek == INIT_SRC_POS)
		peek++;
	peek++;
	if (peek >= src->buf_size)
		return (ERR_OUT_OF_BOUNDS);
	*c = src->buf[peek];
	return (SUCCESS);
}
