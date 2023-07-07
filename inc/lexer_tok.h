/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:52:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 21:09:35 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_H
# define LEXER_TOK_H

/* ====== Includes ====== */

//# include "minishell.h"
# include "lexer_src.h"
# include "lexer_utils.h"
# include "minishell_error.h"

/* ====== Definitions ====== */

typedef struct s_tok
{
	char	*tok;
	int		tok_size;
}	t_tok;

/* ====== Functions ====== */

t_error	ft_tokenise(t_src *src, t_tok *token);
t_error	ft_create_tok(t_tok *token, char *s);
void	ft_free_tok(t_tok *tok);
t_error	ft_add_to_buf(char c, char *buf, int *buf_size, int *buf_pos);
t_error	ft_partition(t_src *src, char *buf, int *buf_pos, int *buf_size);

#endif