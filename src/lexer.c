/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/10 19:50:42 by gwolf            ###   ########.fr       */
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
 * @param lst_head	Head node of token list.
 * @param input 	Input string to be tokenised.
 * @return t_err 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_lex_input(t_tkn_list	**lst_head, char *input)
{
	t_src	src;
	t_err	err;
	t_tok	token;

	ft_init_lexer(&src, input, ft_strlen(input));
	err = ft_tokenise(&src, &token);
	while (err != ERR_EOF || !*lst_head)
	{
		err = ft_new_node(lst_head, token.str);
		if (err != SUCCESS)
		{
			ft_free_lst(lst_head);
			ft_free_tok(&token);
			return (err);
		}
		err = ft_tokenise(&src, &token);
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
