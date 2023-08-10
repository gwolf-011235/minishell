/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:36:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 21:39:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stddef.h>

# include "minishell_config.h"
# include "minishell_error.h"
# include "minishell_utils.h"

/**
 * @brief Buffer structure.
 *
 * Contains temporary buffer string which is to be
 * saved inside the token.
 * @param str		Buffer string.
 * @param size		Size of malloced buffer memory in Bytes.
 * @param cur_pos	Current position inside malloced buffer
 * 					memory.
 */
typedef struct s_buf
{
	char	*str;
	int		size;
	int		cur_pos;
}	t_buf;

t_err	ft_buf_init(t_buf *buf);
t_err	ft_buf_clear(t_buf *buf);
t_err	ft_buf_double(t_buf *buf);
t_err	ft_buf_strlcpy(t_buf *buf, char *str, size_t len);

#endif