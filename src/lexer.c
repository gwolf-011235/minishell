/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/25 20:07:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_list.c
 * @brief Contains functions to create a double-linked list of tokens.
 */

#include "mod_lexer.h"
/* #include "lexer_list.h"
#include "lexer_utils.h"
#include "lexer_tok_utils.h" */

/**
 * @brief Create a list of token.
 *
 * Loops through input, creates token until no more
 * chars are found and returns ERR_EOF which breaks the loop.
 * Creates initial node even if first token ends directly with ERR_EOF.
 * Handles errors.
 * @param lst_head	Head node of token list.
 * @param input 	Input string to be tokenised.
 * @return t_err 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_lex_input(t_tkn_list **lst_head, char *input, t_buf *buf)
{
	t_src	src;
	t_err	err;
	t_tok	token;

	ft_init_lexer(&src, input, ft_strlen(input));
	ft_buf_clear(buf);
	err = ft_tokenise(&src, &token, buf);
	if (err == ERR_MALLOC)
		return (ft_print_error(ERR_LEXER));
	while (err != ERR_EOF || !*lst_head)
	{
		if (ft_new_node(lst_head, token.str) == ERR_MALLOC)
			ft_lex_err(lst_head, &token);
		err = ft_tokenise(&src, &token, buf);
		if (err == ERR_MALLOC)
			ft_lex_err(lst_head, &token);
	}
	ft_assign_type(*lst_head);
	return (SUCCESS);
}

/**
 * @brief Initate the lexer.
 *
 * Fills source struct with values from the input string.
 * @param src 		Struct containing data on input/source string.
 * @param input 	Input string.
 */
void	ft_init_lexer(t_src *src, char *input, int len)
{
	src->buf = input;
	src->buf_size = len;
	src->cur_pos = INIT_SRC_POS;
}

/**
 * @brief	Handle ERR_MALLOC in lexer.
 *
 * Clears token list.
 * Frees token, if token string malloced.
 * Return err message.
 * @param lst_head		Head of token list.
 * @param token			Current malloced token.
 * @return t_err		ERR_LEXER
 */
t_err	ft_lex_err(t_tkn_list **lst_head, t_tok *token)
{
	g_status = 1;
	ft_free_lst(lst_head);
	ft_free_tok(token);
	return (ft_print_error(ERR_LEXER));
}
