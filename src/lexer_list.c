/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 14:37:37 by sqiu             ###   ########.fr       */
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
 * @param lst_head	Head node of token list.
 * @param input 	Input string to be tokenised.
 * @return t_err 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_err	ft_lex_input(t_tkn_list	*lst_head, char *input)
{
	t_src	src;
	t_err	err;
	t_tok	token;	

	ft_init_lexer(&src, input);
	err = ft_tokenise(&src, &token);
	while (err != ERR_EOF || !lst_head)
	{
		err = ft_new_node(lst_head, token.str);
		if (err != SUCCESS)
		{
			ft_free_lst(&lst_head);
			ft_free_tok(&token);
			return (err);
		}
		err = ft_tokenise(&src, &token);
	}
	return (SUCCESS);
}

/**
 * @brief Initate the lexer.
 *
 * Fills source struct with values from the input string.
 * @param src 		Struct containing data on input/source string.
 * @param input 	Input string.
 */
void	ft_init_lexer(t_src *src, char *input)
{
	src->buf = input;
	src->buf_size = ft_strlen(input);
	src->cur_pos = INIT_SRC_POS;
}

/**
 * @brief Create a new node and add it to the end of the token list.
 *
 * @param lst_head	Head node of token list.
 * @param content	Content string to be written into new node.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_new_node(t_tkn_list	*lst_head, char *content)
{
	t_tkn_list	*new;

	new = (t_tkn_list *)malloc(sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	ft_add_lst(&lst_head, new);
	return (SUCCESS);
}

/**
 * @brief Iterate through token list and free all nodes.
 *
 * @param lst Token list to be freed.
 * @param del Pointer to function used for clean up.
 */
void	ft_free_lst(t_tkn_list **lst)
{
	t_tkn_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		ft_del_node((*lst));
		*lst = tmp;
	}
	(*lst) = NULL;
}

/**
 * @brief Go to end of token list and connect given token.
 *
 * If there is a (last) node in the list, connect new token to the end.
 * If the list is yet empty, set new token as head of the list.
 * @param lst Token list.
 * @param new Given token to be added to token list.
 */
void	ft_add_lst(t_tkn_list **lst, t_tkn_list *new)
{
	t_tkn_list	*tmp;

	tmp = ft_last(*lst);
	if (tmp)
	{
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}
