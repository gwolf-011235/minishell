/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:18 by sqiu              #+#    #+#             */
/*   Updated: 2023/06/26 16:50:31 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

int	ft_skip_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}

t_error	ft_extract_str(char *src, char *dst)
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
}
