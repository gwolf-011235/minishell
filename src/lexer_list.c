/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/11 11:08:03 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_list.h"

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
			ft_free_lst(&data->lst_head, &ft_del_content);
			ft_free_tok(&data->token);
			return (err);
		}
		ft_init_tok(data);
		err = ft_tokenise(&src, &data->token);
	}
	return (SUCCESS);
}

void	ft_init_lexer(t_src *src, char *input)
{
	src->buf = input;
	src->buf_size = ft_strlen(input);
	src->cur_pos = INIT_SRC_POS;
}

t_error	ft_new_node(t_data *data, char *content)
{
	t_tkn_list	*new;
	t_tkn_list	*prev;

	new = (t_tkn_list *)malloc(sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = content;
	new->next = NULL;
	ft_add_list(&data->lst_head, new);
	return (SUCCESS);
}

void	ft_free_lst(t_tkn_list **lst, void (*del)(void*))
{
	t_tkn_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		ft_del_node((*lst), del);
		*lst = tmp;
	}
	(*lst) = NULL;
}

void	ft_del_node(t_tkn_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst -> content);
	free(lst);
}

void	ft_del_content(void *s)
{
	if (!s)
		return ;
	s = "";
}

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
