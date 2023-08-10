/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:51:22 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 16:32:58by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_field_split.c
 * @brief Functions to perform field splitting on expanded parts of str.
 */
#include "mod_expand.h"

/**
 * @brief Splits an expanded node into several words.
 *
 * Count the words with ft_count_expand_words().
 * If one word return.
 * If more words:
 * Setup buffer with ft_init_buf().
 * Split into several words with ft_split_node().
 * Del old node and update list pointer with ft_del_old_node().
 * @param input Pointer to tracker.
 * @param list Pointer pointer to the current node.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_field_split(t_track *input, t_tkn_list **list)
{
	t_tkn_list	*tmp;
	t_buf		buf;
	t_err		err;
	size_t		words;

	tmp = *list;
	words = 0;
	ft_count_expand_words(input, &words);
	if (words == 1)
		return (ERR_NOSPLIT);
	else
	{
		err = ft_init_buf(&buf);
		if (err != SUCCESS)
			return (err);
		err = ft_split_node(input, &tmp, &buf);
		free(buf.str);
		if (err != SUCCESS)
			return (err);
		ft_del_old_node(tmp, &words);
	}
	*list = tmp;
	return (SUCCESS);
}

/**
 * @brief Count how many words will be after splitting.
 *
 * Set tracker->pos to beginning of expanded part.
 * If the pos is bigger than 0, then something is before the expanded part.
 * Set words to one and skip all spaces to get to next word.
 * Looping through the str, delimited by expand len:
 * If pos is 0 and str is not space increase words.
 * If str is space but the next pos isn't increase words.
 * If expanded part ends with space, but there is still stuff after it increase words.
 * @param input Pointer to tracker.
 * @param words Pointer to where to save count:
 * @return t_err SUCCESS
 */
t_err	ft_count_expand_words(t_track *input, size_t *words)
{
	int	last_expand_len;

	last_expand_len = input->last_expand_len;
	input->pos = input->pos - input->last_expand_len;
	if (input->pos != 0)
	{
		*words = 1;
		while (input->str[input->pos] && input->str[input->pos] != ' ')
			(input->pos)++;
	}
	while (input->str[input->pos] && last_expand_len--)
	{
		if (input->pos == 0 && input->str[input->pos] != ' ')
			(*words)++;
		else if (input->str[input->pos] == ' '
			&& input->str[input->pos + 1] != ' '
			&& input->str[input->pos + 1] != '\0')
			(*words)++;
		input->pos++;
	}
	if (input->str[input->pos - 1] == ' ' && input->str[input->pos])
		(*words)++;
	return (SUCCESS);
}

/**
 * @brief Split a node into words.
 *
 * See also ft_lex_input().
 * Difference: uses ft_better_tokenize() which receives a buffer.
 * And ft_new_node_mid() to insert the node inbetween.
 * @param lst_head Pointer to the current node.
 * @param buf Pointer to the malloced buffer.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_split_node(t_track *input, t_tkn_list **lst_head, t_buf *buf)
{
	t_src	src;
	t_tok	token;
	t_err	err;

	if (input->pos - input->last_expand_len != 0)
		ft_strlcpy_into_buf(buf, input->str, input->pos - input->last_expand_len + 1);
	ft_init_lexer(&src, &(input->str[input->pos - input->last_expand_len]), input->last_expand_len);
	err = ft_better_tokenise(&src, &token, buf, input);
	while (err != ERR_EOF || !*lst_head)
	{
		err = ft_new_node_mid(lst_head, token.str);
		if (err != SUCCESS)
		{
			ft_free_tok(&token);
			return (err);
		}
		buf->cur_pos = 0;
		err = ft_better_tokenise(&src, &token, buf, input);
	}
	return (SUCCESS);
}

/**
 * @brief Deletes node, which was split and corrects pointer position.
 *
 * @param list Pointer to the last inserted word
 * @param words How many words have been created.
 * @return t_err SUCCESS
 */
t_err	ft_del_old_node(t_tkn_list *list, size_t *words)
{
	size_t		i;

	i = 0;
	while (i++ < *words)
		list = list->prev;
	ft_del_node_mid(&list);
	return (SUCCESS);
}
