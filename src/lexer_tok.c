/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:51:59 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/14 13:57:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_tok.h"

/**
 * @brief Create a token.
 * 
 * Token contains the token string and its length.
 * @param token 	Created token.
 * @param s 		Token string.
 * @return t_error 	ERR_MALLOC, ERR_EMPTY, SUCCESS
 */
t_error	ft_create_tok(t_tok *token, char *s)
{
	if (!token || !s)
		return (ERR_EMPTY);
	token->tok_size = ft_strlen(s);
	if (!token->tok_size)
		return (ERR_EOF);
	token->tok = malloc(token->tok_size + 1);
	if (!token->tok)
		return (ERR_MALLOC);
	ft_memcpy(token->tok, s, token->tok_size);
	token->tok[token->tok_size] = '\0';
	return (SUCCESS);
}

/**
 * @brief Overarching function to create a token.
 * 
 * Divides input string into separate tokens. The token string
 * is extracted into a buffer string before being saved inside
 * a token.
 * @param src 		Struct containing the input string,
 * 					its length and current position.
 * @param token 	Token to be created.
 * @return t_error* ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_error	ft_tokenise(t_src *src, t_tok *token)
{
	char	*buf;
	int		buf_size;
	int		buf_pos;
	t_error	err;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	buf_size = 2048;
	buf = malloc(buf_size);
	if (!buf)
		return (ERR_MALLOC);
	buf_pos = 0;
	buf[0] = '\0';
	err = ft_partition(src, buf, &buf_pos, &buf_size);
	if (buf_pos >= buf_size)
		buf_pos--;
	buf[buf_pos] = '\0';
	if (err == ERR_EOF)
		ft_create_tok(token, buf);
	else
		err = ft_create_tok(token, buf);
	free(buf);
	return (err);
}

/**
 * @brief Iterate through input string and step out at predefined delimiters.
 * 
 * Fills buffer string until delimiters are reached.
 * Delimiters: Space, tab, newline, pipe
 * @param src 		Struct containing the input string,
 * 					its length and current position.
 * @param buf 		Buffer string to be filled.
 * @param buf_pos 	Current position in buffer string.
 * @param buf_size 	Buffer malloced size. 
 * @return t_error 	ERR_EMPTY, ERR_EOF, SUCCESS
 */
t_error	ft_partition(t_src *src, char *buf, int *buf_pos, int *buf_size)
{
	char	c;
	t_error	err;

	err = ft_init_partition(src, &c);
	while (err != ERR_EOF)
	{
		if ((c == ' ' || c == '\t') && *buf_pos > 0)
			break ;
		else if ((c == '\n' || c == '|') && *buf_pos > 0)
		{
			ft_unget_char(src);
			break ;
		}
		else
		{
			ft_add_to_buf(c, buf, buf_size, buf_pos);
			if (c == '\n' || c == '|')
				break ;
		}
		err = ft_next_char(src, &c);
	}
	if (err == ERR_EOF)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Initate the partitioning.
 * 
 * Skip all initial spaces and tabs of source string.
 * Retrieve the first character.
 * @param src 		Struct containing the source string.
 * @param c 		Character retrieved.
 * @return t_error 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_error	ft_init_partition(t_src *src, char *c)
{
	t_error	err;

	err = ft_skip_space(src);
	err = ft_next_char(src, c);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
