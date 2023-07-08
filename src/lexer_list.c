/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:57:22 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/08 18:33:41 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_list.h"

t_error	ft_list_token(t_data *data, char *input)
{
	t_src		src;
	t_tok		token;
	t_error		err;
	t_tkn_list	*new;
	t_tkn_list	*prev;

	src.buf = input;
	src.buf_size = ft_strlen(input);
	src.cur_pos = INIT_SRC_POS;
	new = NULL;
	prev = data->lst_head;
	err = ft_tokenise(&src, &token);
	while (err != ERR_EOF)
	{
		err = ft_new_node(new, &prev, token.tok);
		if (err != SUCCESS)
		{
			ft_free_lst(&data->lst_head, &ft_del_content);
			ft_free_tok(&token);
			return (err);
		}
		//ft_add_list(&data->lst_head, new);
		prev = new;
		ft_free_tok(&token);
		free(new);
		err = ft_tokenise(&src, &token);
	}
	return (SUCCESS);
}

t_error	ft_new_node(t_tkn_list *new, t_tkn_list **prev, char *s)
{
	new = malloc (sizeof(t_tkn_list));
	if (!new)
		return (ERR_MALLOC);
	new->content = s;
	new->next = NULL;
	if (*prev)
		new->prev = *prev;
	else
	{
		new->prev = NULL;
		*prev = new;
	}
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
		tmp -> next = new;
	else
		*lst = new;
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
