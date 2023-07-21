/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_src.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:27:37 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/19 22:52:46 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_SRC_H
# define LEXER_SRC_H

/* ====== Includes ====== */

//# include "minishell.h"

/* ====== Definitions ====== */

# define INIT_SRC_POS -2

typedef struct s_src
{
	char	*buf;
	int		buf_size;
	int		cur_pos;	
}	t_src;

/* ====== Functions ====== */

t_error	ft_next_char(t_src *src, char *c);
t_error	ft_unget_char(t_src *src);
t_error	ft_peek_char(t_src *src, char *c);

#endif