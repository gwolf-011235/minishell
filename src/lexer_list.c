/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/14 19:38:13 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_list.c
 * @brief Contains functions to create a double-linked list of tokens.
 */
#include "minishell.h"
#include "lexer_list.h"
#include "lexer_utils.h"

/**
 * @brief Create a list of token.
 * 
 * @param data 		Overarching struct containing all meta data.
 * @param input 	Input string to be tokenised.
 * @return t_error 	ERR_EMPTY, ERR_MALLOC, SUCCESS
 */
t_error	ft_list_token(t_data *data, char *input)
{
	t_src		src;
	t_error		err;

	ft_init_lexer(&src, input);
	err = ft_tokenise(&src, &data->token);
	while (err != ERR_EOF || !data->lst_head)
	{
		err = ft_new_node(data, data->token.tok);
		if (err != SUCCESS)
		{
			ft_free_lst(&data->lst_head);
			ft_free_tok(&data->token);
			return (err);
		}
		err = ft_tokenise(&src, &data->token);
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
 * @param data		Overarching struct containing all meta data.
 * @param content	Content string to be written into new node.
 * @return t_error 	ERR_MALLOC, SUCCESS
 */
t_error	ft_new_node(t_data *data, char *content)
{
	t_tkn_list	*new;

	new = (t_tkn_list *)malloc(sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	ft_add_list(&data->lst_head, new);
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
void	ft_add_list(t_tkn_list **lst, t_tkn_list *new)
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
