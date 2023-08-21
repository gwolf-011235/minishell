/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:34:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/21 18:22:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file buffer.c
 * @brief Functions for handling the buffer.
 */
#include "buffer.h"

/**
 * @brief Initiates a t_buf buffer
 *
 * @param buf Pointer to buffer
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_buf_init(t_buf *buf)
{
	t_err	err;

	buf->size = BUF_SIZE;
	err = ft_err_malloc((void **)&buf->str, buf->size,
			"minishell: ft_buf_init");
	if (err != SUCCESS)
		return (err);
	ft_buf_clear(buf);
	return (SUCCESS);
}

/**
 * @brief Destroy the buffer.
 *
 * @param buf Pointer to buffer.
 */
void	ft_buf_destroy(t_buf *buf)
{
	free(buf->str);
	buf->str = NULL;
}

/**
 * @brief Set the buffer to zero.
 *
 * @param buf Pointer to buffer.
 * @return t_err SUCCESS
 */
t_err	ft_buf_clear(t_buf *buf)
{
	ft_memset(buf->str, '\0', buf->size);
	buf->cur_pos = 0;
	return (SUCCESS);
}

/**
 * @brief Reallocs buffer into double its size
 *
 * @param buf Pointer to buffer.
 * @return t_err SUCCESS, ERR_MALLOC
 */
t_err	ft_buf_double(t_buf *buf)
{
	char	*temp;

	errno = 0;
	temp = ft_realloc(buf->str, (buf->size * 2), buf->size);
	if (!temp)
	{
		perror("minishell: ft_buf_double");
		return (ERR_MALLOC);
	}
	buf->str = temp;
	buf->size *= 2;
	return (SUCCESS);
}

/**
 * @brief Copy str into buffer using strlcpy.
 *
 * If str to copy would be too big, double buffer size.
 * ft_strlcpy() accounts for zero terminator.
 * This means generally that passed len needs to be incr +1.
 * @param buf Pointer to buffer.
 * @param str String to copy.
 * @param len Len of string accounted with zero terminator.
 * @return t_err
 */
t_err	ft_buf_strlcpy(t_buf *buf, char *str, size_t len)
{
	t_err	err;

	if ((int)len + buf->cur_pos > buf->size)
	{
		err = ft_buf_double(buf);
		if (err != SUCCESS)
			return (err);
	}
	ft_strlcpy(&buf->str[buf->cur_pos], str, len);
	buf->cur_pos += len - 1;
	buf->str[buf->cur_pos] = '\0';
	return (SUCCESS);
}
