/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:46:44 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/18 18:28:44 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_tok_utils.c
 * @brief Contains helper functions for tokenising.
 */
#include "mod_lexer.h"
/* #include "lexer_src.h"
#include "lexer_tok.h"
#include "lexer_tok_utils.h" */

/**
 * @brief Free token string.
 *
 * @param token Token to be freed.
 */
void	ft_free_tok(t_tok *token)
{
	if (token->str)
		free(token->str);
}

/**
 * @brief Add character to buffer string.
 *
 * In case the buffer string is not long enough, its size is doubled.
 * @param c 		Character to be added.
 * @param buf 		Temporary buffer to save as token.
 */
void	ft_add_to_buf(char c, t_buf *buf)
{
	buf->str[buf->cur_pos] = c;
	buf->cur_pos++;
}

/**
 * @brief Check if next char is a redirect.
 *
 * If yes, save next char as well into buf.
 * @param src 		Struct containing the input string,
 * 					its length and current position.
 * @param c 		Special char: \n, |, < or >
 * @param buf 		Temporary buffer to save as token.
 * @return t_err 	SUCCESS, ERR_EMPTY, ERR_OUT_OF_BOUNDS
 */
t_err	ft_check_double_redirect(t_src *src, char *c, t_buf *buf)
{
	char	next;
	t_err	err;

	err = ft_peek_char(src, &next);
	if (err != SUCCESS)
		return (err);
	if (ft_strchr("<>", *c) && next == *c)
	{
		ft_next_char(src, c);
		ft_add_to_buf(*c, buf);
	}
	return (SUCCESS);
}
