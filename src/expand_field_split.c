/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:34:57 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 21:49:52 by gwolf            ###   ########.fr       */
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
 * Clear buffer with ft_buf_clear().
 * Split into several words with ft_split_node().
 * Del old node with ft_del_prev_n() and update list pointer.
 * @param input Pointer to tracker.
 * @param cur_node Pointer pointer to the current node.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_NOSPLIT
 */
t_err	ft_field_split(t_track *input, t_tkn_list **cur_node, t_buf *buf)
{
	t_tkn_list	*tmp;
	size_t		words;

	tmp = *cur_node;
	words = 0;
	ft_count_expand_words(input, &words, input->last_expand_len);
	if (words == 1)
		return (ft_trim_single_word(input));
	else
	{
		ft_buf_clear(buf);
		if (ft_split_node(input, &tmp, buf) == ERR_MALLOC)
			return (ERR_MALLOC);
		ft_del_prev_n(tmp, words);
	}
	*cur_node = tmp;
	return (SUCCESS);
}

/**
 * @brief Count how many words will be after splitting.
 *
 * Set tracker->pos to beginning of expanded part.
 * If the pos is bigger than 0, then something is before
 * expanded part -> Set words to one and skip all spaces to get to next word.
 * Looping through the str, delimited by expand len:
 * If pos is 0 and str is not space incr words.
 * If str is space but the next pos isn't incr words.
 * @param input Pointer to tracker.
 * @param words Pointer to where to save count:
 */
void	ft_count_expand_words(t_track *input, size_t *words,
			int last_expand_len)
{
	input->pos = input->pos - input->last_expand_len;
	if (input->pos != 0)
	{
		*words = 1;
		while (input->str[input->pos] && input->str[input->pos] != ' '
			&& last_expand_len)
		{
			(input->pos)++;
			last_expand_len--;
		}
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
}

/**
 * @brief Split a node into words.
 *
 * Based on ft_lex_input().
 * Calc pos beforen expansion.
 * If not zero copy everything before expand into buf.
 * Init t_src with ft_init_lexer() where len is expand_len.
 * Use ft_better_tokenize() to create token.
 * In loop add node and call ft_better_tokenize() again.
 * @param input Pointer to tracker.
 * @param cur_node Pointer to the current node.
 * @param buf Pointer to buffer.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_split_node(t_track *input, t_tkn_list **cur_node, t_buf *buf)
{
	t_src	src;
	t_tok	token;
	t_err	err;
	size_t	old_pos;

	old_pos = input->pos - input->last_expand_len;
	if (old_pos != 0)
		if (ft_buf_strlcpy(buf, input->str, old_pos + 1) == ERR_MALLOC)
			return (ERR_MALLOC);
	ft_init_lexer(&src, &(input->str[old_pos]), input->last_expand_len);
	err = ft_tokenise_fs(&src, &token, buf, input);
	if (err == ERR_MALLOC)
		return (err);
	while (err != ERR_EOF || !*cur_node)
	{
		if (ft_new_node_mid(cur_node, token.str) == ERR_MALLOC)
			return (ft_split_err(&token));
		buf->cur_pos = 0;
		err = ft_tokenise_fs(&src, &token, buf, input);
		if (err == ERR_MALLOC)
			return (err);
	}
	return (SUCCESS);
}

/**
 * @brief Tokenise a string while field split.
 *
 * Based on ft_tokenise(), adapted for field split.
 * Does not set buffer->cur_pos to zero, something could already be in there.
 * Uses partition_fs() to fill buffer.
 * If field splitting is at end of expand_len (src_>cur_pos == src_buf_size) and
 * after the expansion are still chars, they get copied into buffer with
 * ft_buf_strlcpy().
 * Creates a new token with ft_create_tok().
 * @param src The string to tokenize.
 * @param token Where to save the token.
 * @param buf A pre malloced buffer.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_EOF
 */
t_err	ft_tokenise_fs(t_src *src, t_tok *token, t_buf *buf, t_track *input)
{
	t_err	err;

	if (ft_partition_fs(src, buf) == ERR_MALLOC)
		return (ERR_MALLOC);
	buf->str[buf->cur_pos] = '\0';
	if (src->cur_pos == src->buf_size && input->str[input->pos])
		if (ft_buf_strlcpy(buf, (input->str + input->pos),
				ft_strlen(input->str + input->pos) + 1) == ERR_MALLOC)
			return (ERR_MALLOC);
	err = ft_create_tok(token, buf->str);
	return (err);
}

/**
 * @brief Fills buffer with a piece of string.
 *
 * Based on ft_partition(), adapted for field split.
 * Difference:
 * Check if buffer has char saved (stuff before expand) and src is at INIT_POS:
 * If next char is space (from the expansion) the token is already finished.
 * Fewer break conditions since expanded chars don't have special meaning.
 * @param src The tokenized string.
 * @param buf Pointer to pre malloced buffer.
 * @return t_err ERR_EOF, ERR_MALLOC
 */
t_err	ft_partition_fs(t_src *src, t_buf *buf)
{
	char	c;
	t_err	err;

	c = 0;
	if (src->cur_pos == INIT_SRC_POS && buf->cur_pos != 0)
	{
		ft_peek_char(src, &c);
		if (c == ' ' || c == '\t')
			return (SUCCESS);
	}
	ft_skip_space(src);
	err = ft_next_char(src, &c);
	while (err != ERR_EOF)
	{
		if ((c == ' ' || c == '\t') && buf->cur_pos > 0)
			break ;
		else
			if (ft_add_to_buf(c, buf) == ERR_MALLOC)
				return (ERR_MALLOC);
		err = ft_next_char(src, &c);
	}
	return (err);
}
