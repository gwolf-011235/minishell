/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:51:59 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/25 17:10:59 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_tok.c
 * @brief Contains functions to create tokens.
 */
#include "mod_lexer.h"

/**
 * @brief Create a token.
 *
 * Token contains the token string and its length.
 * @param token 	Created token.
 * @param s 		Token string.
 * @return t_err 	ERR_MALLOC, ERR_EOF, SUCCESS
 */
t_err	ft_create_tok(t_tok *token, char *s)
{
	token->size = ft_strlen(s);
	if (!token->size)
		return (ERR_EOF);
	if (ft_err_strdup(s, &token->str, "minishell: malloc")
		== ERR_MALLOC)
		return (ERR_MALLOC);
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
 * @return t_err* ERR_MALLOC, SUCCESS
 */
t_err	ft_tokenise(t_src *src, t_tok *token, t_buf *buf)
{
	t_err	err;

	buf->cur_pos = 0;
	buf->str[0] = '\0';
	if (ft_partition(src, buf) == ERR_MALLOC)
		return (ERR_MALLOC);
	buf->str[buf->cur_pos] = '\0';
	err = ft_create_tok(token, buf->str);
	return (err);
}

/**
 * @brief Iterate through input string and step out at predefined delimiters.
 *
 * Fills buffer string until delimiters are reached.
 * Delimiters: Space, tab, newline, pipe
 * @param src 		Struct containing the input string,
 * 					its length and current position.
 * @param buf 		Temporary buffer to save as token.
 * @return t_err 	ERR_EOF, SUCCESS
 */
t_err	ft_partition(t_src *src, t_buf *buf)
{
	char	c;
	t_err	err;

	err = ft_init_partition(src, &c);
	while (err != ERR_EOF)
	{
		if (c == '"' || c == '\'')
		{
			if (ft_add_quoted_str(c, src, buf) == ERR_MALLOC)
				return (ERR_MALLOC);
		}
		else if ((c == ' ' || c == '\t') && buf->cur_pos > 0)
			break ;
		else if (ft_strchr("\n|<>", c) && buf->cur_pos > 0)
			return (ft_unget_char(src));
		else
		{
			if (ft_add_to_buf(c, buf) == ERR_MALLOC)
				return (ERR_MALLOC);
			if (ft_strchr("\n|<>", c))
				return (ft_check_double_redirect(src, &c, buf));
		}
		err = ft_next_char(src, &c);
	}
	return (err);
}

/**
 * @brief Initate the partitioning.
 *
 * Skip all initial spaces and tabs of source string.
 * Retrieve the first character.
 * @param src 		Struct containing the source string.
 * @param c 		Character retrieved.
 * @return t_err 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_init_partition(t_src *src, char *c)
{
	t_err	err;

	err = ft_skip_space(src);
	err = ft_next_char(src, c);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Add anything inside of quotes.
 *
 * @param quote Either ' or "
 * @param src 	Struct containing the source string.
 * @param buf 	Temporary buffer to save as token.
 * @return SUCCESS, ERR_MALLOC
 */
t_err	ft_add_quoted_str(char quote, t_src *src, t_buf *buf)
{
	char	c;
	bool	first_loop;

	c = quote;
	first_loop = 1;
	while (c != quote || first_loop == 1)
	{
		if (ft_add_to_buf(c, buf) == ERR_MALLOC)
			return (ERR_MALLOC);
		ft_next_char(src, &c);
		first_loop = 0;
	}
	if (ft_add_to_buf(c, buf) == ERR_MALLOC)
		return (ERR_MALLOC);
	return (SUCCESS);
}
