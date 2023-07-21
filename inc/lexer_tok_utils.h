/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:47:14 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOK_UTILS_H
# define LEXER_TOK_UTILS_H

/* ====== Functions ====== */

void	ft_free_tok(t_tok *token);
t_err	ft_add_to_buf(char c, t_buf *tmp);
t_err	ft_check_double_redirect(t_src *src, char *c, t_buf *tmp);

#endif