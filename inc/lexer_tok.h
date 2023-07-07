/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:52:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/07 14:38:22 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_H
# define LEXER_TOK_H

/* ====== Includes ====== */

# include "minishell.h"
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

t_error	*ft_tokenise(t_src *src, t_tok *token);
void	ft_free_tok(t_tok *tok);

#endif