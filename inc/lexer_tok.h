/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:52:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_H
# define LEXER_TOK_H

/* ====== Definitions ====== */

typedef struct s_buf
{
	char	*str;
	int		size;
	int		cur_pos;	
}	t_buf;

/* ====== Functions ====== */

t_err	ft_tokenise(t_src *src, t_tok *token);
t_err	ft_create_tok(t_tok *token, char *s);
t_err	ft_partition(t_src *src, t_buf *tmp);
t_err	ft_init_partition(t_src *src, char *c);
void	ft_add_quoted_str(char quote, t_src *src, t_buf *tmp);

#endif