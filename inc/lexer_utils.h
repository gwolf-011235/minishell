/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/06/26 16:50:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

/* ====== Includes ====== */

# include "minishell.h"

/* ====== Functions ====== */

int		ft_skip_space(char *s);
t_error	ft_extract_str(char *src, char *dst);

#endif