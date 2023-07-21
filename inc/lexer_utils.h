/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

/* ====== Includes ====== */

//# include "minishell.h"
# include "lexer_src.h"

/* ====== Functions ====== */

t_err		ft_skip_space(t_src *src);
t_tkn_list	*ft_last(t_tkn_list *lst);
void		ft_del_node(t_tkn_list *lst);
//t_err	ft_extract_str(char *src, char *dst);

#endif