/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:46:44 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/19 23:29:31 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_tok_utils.c
 * @brief Contains helper functions for tokenising.
 */
#include "minishell.h"
#include "lexer_src.h"
#include "lexer_tok.h"
#include "lexer_tok_utils.h"

/**
 * @brief Free token string.
 * 
 * @param token Token to be freed.
 */
void	ft_free_tok(t_tok *token)
{
	if (token->tok)
		free(token->tok);
}

/**
 * @brief Add character to buffer string.
 * 
 * In case the buffer string is not long enough, its size is doubled.
 * @param c 		Character to be added.
 * @param buf 		Buffer string.
 * @param buf_size 	Buffer string length.
 * @param buf_pos 	Current position in buffer string.
 * @return t_error 	ERR_MALLOC, SUCCESS
 */
t_error	ft_add_to_buf(char c, t_buf *tmp)
{
	char	*temp;

	tmp->str[tmp->cur_pos] = c;
	tmp->cur_pos++;
	if (tmp->cur_pos >= tmp->size)
	{
		temp = ft_realloc(tmp->str, (tmp->size * 2), tmp->size);
		if (!temp)
			return (ERR_MALLOC);
		tmp->str = temp;
		tmp->size *= 2;
	}
	return (SUCCESS);
}

t_error	ft_add_double_redirect(t_src *src, char *c, t_buf *tmp)
{
	char	next;
	t_error	err;

	err = ft_peek_char(src, &next);
	if (err != SUCCESS)
		return (err);
	if (ft_strchr("<>", *c) && next == *c)
	{
		ft_next_char(src, c);
		ft_add_to_buf(*c, tmp);
	}
	return (SUCCESS);
}
