/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:51:59 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/14 19:46:50 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_tok.c
 * @brief Contains functions to create tokens.
 */
#include "minishell.h"
#include "lexer_src.h"
#include "lexer_tok.h"
#include "lexer_utils.h"
#include "lexer_tok_utils.h"
#include "minishell_error.h"

/**
 * @brief Create a token.
 * 
 * Token contains the token string and its length.
 * @param token 	Created token.
 * @param s 		Token string.
 * @return t_error 	ERR_MALLOC, ERR_EMPTY, SUCCESS
 */
t_error	ft_create_tok(t_tok *token, char *s, bool eof)
{
	if (!token || !s)
		return (ERR_EMPTY);
	token->size = ft_strlen(s);
	if (!token->size)
		return (ERR_EOF);
	token->tok = malloc(token->size + 1);
	if (!token->tok)
		return (ERR_MALLOC);
	ft_memcpy(token->tok, s, token->size);
	token->tok[token->size] = '\0';
	if (eof)
		return (ERR_EOF);
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
	t_buf	tmp;
	t_error	err;
	bool	eof;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	tmp.size = 2048;
	tmp.str = malloc(tmp.size);
	if (!tmp.str)
		return (ERR_MALLOC);
	tmp.cur_pos = 0;
	tmp.str[0] = '\0';
	err = ft_partition(src, &tmp);
	if (tmp.cur_pos >= tmp.size)
		tmp.cur_pos--;
	tmp.str[tmp.cur_pos] = '\0';
	eof = 0;
	if (err == ERR_EOF)
		eof = 1;
	err = ft_create_tok(token, tmp.str, eof);
	free(tmp.str);
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
t_error	ft_partition(t_src *src, t_buf *tmp)
{
	char	c;
	t_error	err;

	err = ft_init_partition(src, &c);
	while (err != ERR_EOF)
	{
		if (c == '"' || c == '\'')
			ft_add_quoted_str(c, src, tmp);
		else if ((c == ' ' || c == '\t') && tmp->cur_pos > 0)
			break ;
		else if ((c == '\n' || c == '|') && tmp->cur_pos > 0)
		{
			ft_unget_char(src);
			break ;
		}
		else
		{
			ft_add_to_buf(c, tmp);
			if (c == '\n' || c == '|')
				break ;
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

void	ft_add_quoted_str(char quote, t_src *src, t_buf *tmp)
{
	char	c;
	bool	first_loop;

	c = quote;
	first_loop = 1;
	while (c != quote || first_loop == 1)
	{
		ft_add_to_buf(c, tmp);
		ft_next_char(src, &c);
		first_loop = 0;
	}
	ft_add_to_buf(c, tmp);
}
