/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:52:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/20 00:03:23 by sqiu             ###   ########.fr       */
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

t_error	ft_tokenise(t_src *src, t_tok *token);
t_error	ft_create_tok(t_tok *token, char *s);
t_error	ft_partition(t_src *src, t_buf *tmp);
t_error	ft_init_partition(t_src *src, char *c);
void	ft_add_quoted_str(char quote, t_src *src, t_buf *tmp);

#endif