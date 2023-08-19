/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_syntax.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:45:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 12:17:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_SYNTAX_H
# define MOD_SYNTAX_H

# include <stddef.h>

# include "libft.h"
# include "minishell_error.h"
# include "minishell_utils.h"

/* ====== Globals ====== */

extern __sig_atomic_t	g_status;

/* ====== Typedef ====== */

typedef enum s_syntax
{
	QUOTE,
	NEW_LINE,
	TOKEN
}	t_syntax;

/* ====== Functions ====== */

//syntax.c
t_err	ft_check_syntax(const char *input);
t_err	ft_check_redirect(const char *input, size_t pos, char symbol);
t_err	ft_check_pipe(const char *input, size_t pos);
t_err	ft_quote_skipper(const char *quote_start, size_t *i, char target);
int		ft_is_space(char c);
t_err	ft_syntax_error(t_syntax syntax_err, char c);

#endif
