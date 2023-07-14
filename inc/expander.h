/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 14:14:21 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "minishell_error.h"
# include "hashtable.h"
# include "ft_string.h"

typedef struct s_tok {
	char	*str;
	size_t	len;
}	t_tok;

//expander.c
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);
t_error	ft_insert_replace(char **input, size_t pos, t_tok token, t_tok replace);

//expand_tilde.c
t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos);

//expand_var.c
t_error	ft_expand_var(char **input, t_hashtable *symtab, size_t *pos, t_info *info);

#endif