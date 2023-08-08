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

#include "mod_expand.h"

/**
 * @brief Splits an expanded node into several words.
 *
 * Count the words with ft_count_expand_words().
 * If one word return.
 * If no word delete the node.
 * If more words:
 * Setup buffer with ft_init_buf().
 * Split into several words with ft_split_node().
 * Del old node and update list pointer with ft_del_old_node().
 * @param list Pointer pointer to the current node.
 * @param words Where to save the count.
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
		return (SUCCESS);
	else if (words == 0)
		ft_del_node_mid(&tmp);
	else
	{
		err = ft_init_buf(&buf);
		if (err != SUCCESS)
			return (err);
		err = ft_split_node(&tmp, &buf);
		free(buf.str);
		if (err != SUCCESS)
			return (err);
		ft_del_old_node(&tmp, &words);
	}
	*list = tmp;
	return (SUCCESS);
}

/**
 * @brief Iterate over a quoted part of string.
 *
 * @param quote_start Pointer where opening quote was found.
 * @param i Pointer to current iterator
 * @param target Either single or double quote.
 * @return t_err SUCCESS
 */
t_err	ft_quote_skip(const char *quote_start, size_t *i, char target)
{
	char	*quote_end;

	quote_end = ft_strchr((quote_start + 1), target);
	*i += quote_end - quote_start;
	return (SUCCESS);
}

/**
 * @brief Count how many words will be after splitting.
 *
 * Iterate over string.
 * If a quote is found, skip over the quoted part (it won't get split).
 * If a space preceeds a not space and not a zero temrinator a word is found.
 * A word is also found if the first char is not a space.
 * @param str Pointer to string.
 * @param words Pointer to words variable.
 * @return t_err SUCCESS
 */
t_err	ft_count_expand_words(t_track *input, size_t *words)
{
	input->pos = input->pos - input->last_expand_len;
	if (input->pos != 0)
	{
		*words = 1;
		while (input->str[input->pos] && input->str[input->pos] != ' ')
			(input->pos)++;
	}
	while (input->str[input->pos] && (input->last_expand_len)--)
	{
		if (input->pos == 0 && input->str[input->pos] != ' ')
			(*words)++;
		else if (input->str[input->pos] == ' ' && input->str[input->pos + 1] != ' '
				&& input->str[input->pos + 1] != '\0')
			(*words)++;
		input->pos++;
	}
	if (input->str[input->pos])
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
t_err	ft_split_node(t_tkn_list **lst_head, t_buf *buf)
{
	t_src	src;
	t_err	err;
	t_tok	token;

	ft_init_lexer(&src, (*lst_head)->content);
	err = ft_better_tokenise(&src, &token, buf);
	while (err != ERR_EOF || !*lst_head)
	{
		err = ft_new_node_mid(lst_head, token.str);
		if (err != SUCCESS)
		{
			ft_free_tok(&token);
			return (err);
		}
		buf->cur_pos = 0;
		err = ft_better_tokenise(&src, &token, buf);
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
t_err	ft_del_old_node(t_tkn_list **list, size_t *words)
{
	size_t		i;

	i = 0;
	while (i++ < *words)
		(*list) = (*list)->prev;
	ft_del_node_mid(list);
	return (SUCCESS);
}
