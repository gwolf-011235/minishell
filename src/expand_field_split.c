/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_field_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:51:22 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/04 19:18:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_expand.h"

t_err	ft_quote_skipper(const char *quote_start, size_t *i, char target)
{
	char	*quote_end;

	quote_end = ft_strchr((quote_start + 1), target);
	*i += quote_end - quote_start;
	return (SUCCESS);
}

t_err	ft_count_expand_words(char *str, size_t *words)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_quote_skipper(&str[i], &i, str[i]);
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
			(*words)++;
		if (str[i] != ' ' && i == 0)
			(*words)++;
		i++;
	}
	return (SUCCESS);
}

void	ft_lst_insert(t_tkn_list *cur, t_tkn_list *new)
{
	new->prev = cur->prev;
	if (cur->prev)
		cur->prev->next = new;
	new->next = cur;
	cur->prev = new;
}

t_err	ft_partition_two(t_src *src, t_buf *buf)
{
	char	c;
	t_err	err;

	err = ft_init_partition(src, &c);
	while (err != ERR_EOF)
	{
		if (c == '"' || c == '\'')
			ft_add_quoted_str(c, src, buf);
		else if ((c == ' ' || c == '\t') && buf->cur_pos > 0)
			break ;
		else
		{
			ft_add_to_buf(c, buf);
		}
		err = ft_next_char(src, &c);
	}
	return (err);
}

t_err	ft_better_tokenise(t_src *src, t_tok *token, t_buf *buf)
{
	t_err	err;

	if (!src || !src->buf || !src->buf_size)
		return (ERR_EMPTY);
	err = ft_partition_two(src, &buf);
	if (buf->cur_pos >= buf->size)
		buf->cur_pos--;
	buf->str[buf->cur_pos] = '\0';
	err = ft_create_tok(token, buf->str);
	return (err);
}

t_err	ft_init_buf(t_buf *buf)
{
	buf->size = BUF_SIZE;
	buf->str = malloc(buf->size);
	if (!buf->str)
		return (ERR_MALLOC);
	buf->str[0] = '\0';
	buf->cur_pos = 0;
	return (SUCCESS);
}

t_err	ft_insert_new_node(t_tkn_list **lst_head, char *content)
{
	t_tkn_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	ft_lst_insert(*lst_head, new);
	return (SUCCESS);
}

t_err	ft_split_nodes(t_tkn_list **lst_head, size_t words)
{
	t_src	src;
	t_err	err;
	t_tok	token;
	t_buf	buf;

	ft_init_lexer(&src, (*lst_head)->content);
	err = ft_init_buf(&buf);
	if (err != SUCCESS)
		return (err);
	err = ft_better_tokenise(&src, &token, &buf);
	while (err != ERR_EOF || !*lst_head)
	{
		err = ft_insert_new_node(lst_head, token.str);
		if (err != SUCCESS)
		{
			ft_free_tok(&token);
			return (err);
		}
		err = ft_better_tokenise(&src, &token, &buf);
	}
	return (SUCCESS);
}

t_err	ft_lst_del_inside(t_tkn_list **lst_head)
{
	t_tkn_list	*cur;

	cur = *lst_head;
	*lst_head = cur->next;
	if (cur->next)
		cur->next->prev = cur->prev;
	if (cur->prev)
		cur->prev->next = cur->next;
	ft_del_node(cur);
	return (SUCCESS);
}

t_err	ft_update_ptr(t_tkn_list **list, size_t words)
{
	t_tkn_list	*tmp;
	size_t		i;

	tmp = *list;
	i = 0;
	while (i++ < words)
		(*list) = (*list)->prev;
	ft_lst_del_inside(&tmp);
	return (SUCCESS);
}

t_err	ft_field_split(t_tkn_list **list)
{
	size_t	words;
	char	**split;
	t_err	err;

	words = 0;
	ft_count_expand_words((*list)->content, &words);
	if (words == 1)
		return (SUCCESS);
	else if (words == 0)
		ft_lst_del_inside(list);
	err = ft_split_nodes(list, words);
	if (err != SUCCESS)
		return (err);
	ft_update_ptr(list, words);
	return (SUCCESS);
}
