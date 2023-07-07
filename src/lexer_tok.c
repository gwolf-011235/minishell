/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:51:59 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 15:30:06 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_tok.h"

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
t_error	ft_add_to_buf(char c, char *buf, int *buf_size, int *buf_pos)
{
	char	*tmp;

	buf[*buf_pos++] = c;
	if (*buf_pos >= *buf_size)
	{
		tmp = ft_realloc(buf, (*buf_size * 2), *buf_size);
		if (!tmp)
			return (ERR_MALLOC);
		buf = tmp;
		*buf_size *= 2;
	}
	return (SUCCESS);
}

/**
 * @brief Create a token.
 * 
 * Token contains the token string and its length.
 * @param token 	Created token.
 * @param s 		Token string.
 * @return t_error 	ERR_MALLOC, SUCCESS
 */
t_error	ft_create_tok(t_tok *token, char *s)
{
	char	*tmp;

	token = ft_calloc (1, sizeof(t_tok));
	if (!token)
		return (ERR_MALLOC);
	token->tok_size = ft_strlen(s);
	tmp = malloc (token->tok_size + 1);
	if (!tmp)
	{
		free(token);
		return (ERR_MALLOC);
	}
	ft_memcpy(tmp, s, token->tok_size);
	tmp[token->tok_size] = '\0';
	token->tok = tmp;
	return (SUCCESS);
}

/**
 * @brief Free token and its token string.
 * 
 * @param token Token to be freed.
 */
void	ft_free_tok(t_tok *token)
{
	if (token->tok)
		free(token->tok);
	free(token);
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
t_error	*ft_tokenise(t_src *src, t_tok *token)
{
	char	*buf;
	int		buf_size;
	int		buf_pos;
	t_error	err;

	buf = NULL;
	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	if (!buf)
	{
		buf_size = 2048;
		buf = malloc(buf_size);
		if (!buf)
			return (ERR_MALLOC);
	}
	buf_pos = 0;
	buf[0] = '\0';
	err = ft_partition(src, buf, &buf_pos, &buf_size);
	if (err != SUCCESS)
		return (err);
	if (buf_pos >= buf_size)
		buf_pos--;
	buf[buf_pos] = '\0';
	err = ft_create_tok(token, buf);
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
 * @return t_error 	ERR_EMPTY, EOF, SUCCESS
 */
t_error	ft_partition(t_src *src, char *buf, int *buf_pos, int *buf_size)
{
	char	c;
	t_error	err;

	err = ft_skip_space(src);
	err = ft_next_char(src, &c);
	if (err != SUCCESS)
		return (err);
	while (err != EOF)
	{
		if ((c == ' ' || c == '\t') && *buf_pos > 0)
			break ;
		else if ((c == '\n' || c == '|') && *buf_pos > 0)
			ft_unget_char(src);
		else
		{
			ft_add_to_buf(c, buf, buf_size, buf_pos);
			if (c == '\n' || c == '|')
				break ;
		}
		err = ft_next_char(src, &c);
	}
	if (err == EOF)
		return (err);
	return (SUCCESS);
}

