/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:52:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/14 14:17:18 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_H
# define LEXER_TOK_H

/* ====== Includes ====== */

//# include "minishell.h"
# include "lexer_src.h"
# include "lexer_utils.h"
# include "lexer_tok_utils.h"
# include "minishell_error.h"

/* ====== Definitions ====== */



/* ====== Functions ====== */

t_error	ft_tokenise(t_src *src, t_tok *token);
t_error	ft_create_tok(t_tok *token, char *s, bool eof);
t_error	ft_partition(t_src *src, char *buf, int *buf_pos, int *buf_size);
t_error	ft_init_partition(t_src *src, char *c);

#endif