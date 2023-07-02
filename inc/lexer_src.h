/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_src.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:27:37 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/02 18:40:35 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_SRC_H
# define LEXER_SRC_H

/* ====== Includes ====== */

# include "minishell.h"

/* ====== Definitions ====== */

# define EOF (-1)
# define INIT_SRC_POS (-2)

typedef struct s_src
{
	char	*buf;
	int		buf_size;
	int		cur_pos;	
}	t_src;

/* ====== Functions ====== */

t_error	next_char(t_src *src, char *c);
void	unget_char(t_src *src);
t_error	peek_char(t_src *src, char *c);

#endif