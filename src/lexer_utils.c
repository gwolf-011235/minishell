/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:18 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 16:51:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_utils.c
 * @brief Contains helper functions to create the token list.
 */

#include "mod_lexer.h"
//#include "lexer_utils.h"

/**
 * @brief Skip all spaces and tabs in source string.
 *
 * @param src 		Struct containing source string.
 * @return t_err	ERR_EMPTY, ERR_EOF, SUCCESS
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
 * @brief 	Assigns type to tokens.
 *
 * Order of checks is significant, otherwise
 * the double redirects would never be detected, e.g.
 * < before << would always result into INFILE.
 * @param lst List of tokens.
 */
void	ft_assign_type(t_tkn_list *lst)
{
	while (lst)
	{
		if (ft_strncmp(lst->content, "<<", 2) == 0)
			lst->type = HEREDOC;
		else if (ft_strncmp(lst->content, "<", 1) == 0)
			lst->type = INFILE;
		else if (ft_strncmp(lst->content, ">>", 2) == 0)
			lst->type = APPEND;
		else if (ft_strncmp(lst->content, ">", 1) == 0)
			lst->type = OUTFILE;
		else if (ft_strncmp(lst->content, "|", 1) == 0)
			lst->type = PIPE;
		else if (ft_strncmp(lst->content, "\n", 1) == 0)
			lst->type = NEW_LINE;
		else
			lst->type = ARG;
		lst = lst->next;
	}
}
