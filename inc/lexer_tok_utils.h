/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:47:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/12 22:04:57 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_UTILS_H
# define LEXER_TOK_UTILS_H

/* ====== Includes ====== */

/* ====== Functions ====== */

t_error	ft_init_tok(t_data *data);
void	ft_free_tok(t_tok *token);
t_error	ft_add_to_buf(char c, char *buf, int *buf_size, int *buf_pos);

#endif