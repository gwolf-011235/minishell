/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:18 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_utils.c
 * @brief Contains helper functions to create the token list.
 */
#include "minishell.h"
#include "lexer_utils.h"

/**
 * @brief Skip all spaces and tabs in source string.
 * 
 * @param src 		Struct containing source string.
 * @return t_error	ERR_EMPTY, ERR_EOF, SUCCESS
 */
t_err	ft_skip_space(t_src *src)
{
	char	c;
	t_err	err;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	err = ft_peek_char(src, &c);
	while (err != ERR_OUT_OF_BOUNDS && (c == ' ' || c == '\t'))
	{
		ft_next_char(src, &c);
		err = ft_peek_char(src, &c);
	}
	return (err);
}

/**
 * @brief Delete the content and the node itself.
 * 
 * @param lst List containing the nodes to be deleted.
 * @param del Pointer to function to delete content of nodes.
 */
void	ft_del_node(t_tkn_list *lst)
{
	if (!lst)
		return ;
	free(lst -> content);
	free(lst);
}

/**
 * @brief Iterate to last node of given list.
 * 
 * Returns 0 if list is empty.
 * @param lst 			List to be iterated through.
 * @return t_tkn_list* 	Last node of list.
 */
t_tkn_list	*ft_last(t_tkn_list *lst)
{
	t_tkn_list	*last;

	last = lst;
	while (last)
	{
		if (last -> next == NULL)
			return (last);
		last = last -> next;
	}
	return (0);
}

/* t_error	ft_extract_str(char *src, char *dst)
{
	int	i;
	int	start;

	i = 0;
	while (src[i] == '<' || src[i] == '>')
		i++;
	i += ft_skip_space(src + i);
	start = i;
	while (src[i] != ' ' && src[i] != '|')
		i++;
	dst = malloc(sizeof(char) * (i - start + 1));
	if (!dst)
		return (ERR_MALLOC);
	ft_memmove(dst, src, i - start);
	dst[i] = '\0';
	return (SUCCESS);
} */
