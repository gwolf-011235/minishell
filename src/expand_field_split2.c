/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_split2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:38:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/08 17:37:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

/**
 * @brief Fills buffer with a piece of the string.
 *
 * See also ft_partition().
 * Difference: has fewer break conditions since the expanded chars don't have
 * a special meaning anymore.
 * @param src The tokenized string.
 * @param buf Pointer to pre malloced buffer.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_EOF
 */
t_err	ft_partition_two(t_src *src, t_buf *buf)
{
	char	c;
	t_err	err;

	err = ft_init_partition(src, &c);
	while (err != ERR_EOF)
	{
		if ((c == ' ' || c == '\t') && buf->cur_pos > 0)
			break ;
		else
		{
			err = ft_add_to_buf(c, buf);
			if (err != SUCCESS)
				return (err);
		}
		err = ft_next_char(src, &c);
	}
	return (err);
}

/**
 * @brief Tokenize a string.
 *
 * Better because it doen't malloc a buffer.
 * Uses partition_two() to fill buffer.
 * Creates a new token with ft_create_tok().
 * @param src The string to tokenize.
 * @param token Where to save the token.
 * @param buf A pre malloced buffer.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC, ERR_EOF
 */
t_err	ft_better_tokenise(t_src *src, t_tok *token, t_buf *buf, t_track *input)
{
	t_err	err;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	err = ft_partition_two(src, buf);
	if (buf->cur_pos >= buf->size)
		buf->cur_pos--;
	buf->str[buf->cur_pos] = '\0';
	if (src->cur_pos == src->buf_size && input->str[input->pos])
		ft_strlcpy_into_buf(buf, (input->str + input->pos), ft_strlen(input->str + input->pos));
	err = ft_create_tok(token, buf->str);
	return (err);
}

/**
 * @brief Initiates a t_buf buffer
 *
 * @param buf Pointer to buffer
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_init_buf(t_buf *buf)
{
	buf->size = BUF_SIZE;
	buf->str = malloc(buf->size);
	if (!buf->str)
		return (ERR_MALLOC);
	buf->str[0] = '\0';
	buf->cur_pos = 0;
	return (SUCCESS);
}

t_err	ft_strlcpy_into_buf(t_buf *buf, char *str, size_t len)
{
	ft_strlcpy(&buf->str[buf->cur_pos], str, len);
	buf->cur_pos += len - 1;
	buf->str[buf->cur_pos] = '\0';
	return (SUCCESS);
}