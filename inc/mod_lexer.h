/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:38 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/18 17:23:38 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_LEXER_H
# define MOD_LEXER_H

/* ====== Includes ====== */

# include "mod_handle_input.h"
# include "buffer.h"

/* ====== Structs ====== */

# define INIT_SRC_POS -2

/**
 * @brief Source structure.
 *
 * @param buf		Source string.
 * @param buf_size	Length of source string.
 * @param cur_pos	Current position inside source string.
 */
typedef struct s_src
{
	char	*buf;
	int		buf_size;
	int		cur_pos;
}	t_src;

/**
 * @brief Token structure.
 *
 * Includes token string and the token size.
 * @param str String containing token.
 * @param size Size of token string.
 */
typedef struct s_tok
{
	char	*str;
	int		size;
}	t_tok;

/* ====== Functions ====== */

// initiation
void		ft_init_lexer(t_src *src, char *input, int len);

// src handling
t_err		ft_next_char(t_src *src, char *c);
t_err		ft_unget_char(t_src *src);
t_err		ft_peek_char(t_src *src, char *c);

// buffer handling
t_err		ft_partition(t_src *src, t_buf *tmp);
t_err		ft_init_partition(t_src *src, char *c);
void		ft_add_quoted_str(char quote, t_src *src, t_buf *tmp);
void		ft_add_to_buf(char c, t_buf *tmp);
t_err		ft_check_double_redirect(t_src *src, char *c, t_buf *tmp);

// token handling
t_err		ft_tokenise(t_src *src, t_tok *token, t_buf *buf);
t_err		ft_create_tok(t_tok *token, char *s);
void		ft_free_tok(t_tok *token);

// helpers
t_err		ft_skip_space(t_src *src);
void		ft_assign_type(t_tkn_list *lst);
bool		ft_is_env_assign(char *str);

#endif
