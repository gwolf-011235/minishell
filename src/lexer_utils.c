/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:18 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 21:08:49 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

t_error	ft_skip_space(t_src *src)
{
	char	c;
	t_error	err;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	err = ft_peek_char(src, &c);
	while (err != ERR_EOF && (c == ' ' || c == '\t'))
	{
		ft_next_char(src, &c);
		err = ft_peek_char(src, &c);
	}
	return (err);
}

/* t_error	ft_extract_str(char *src, char *dst)
{
	int	i;
	int	start;

	i = 0;
	while (src[i] == '<' || src[i] == '>')
		i++;
	i += ft_skip_space(src + i);
	start = i;
	while (src[i] != ' ' && src[i] != '|')
		i++;
	dst = malloc(sizeof(char) * (i - start + 1));
	if (!dst)
		return (ERR_MALLOC);
	ft_memmove(dst, src, i - start);
	dst[i] = '\0';
	return (SUCCESS);
} */
