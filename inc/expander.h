/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/17 19:37:39 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "minishell_error.h"
# include "hashtable.h"
# include "ft_string.h"

typedef struct s_str_info {
	char	*str;
	size_t	len;
}	t_str_info;

//expander.c
t_error	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);
t_error	ft_insert_replace(char **input, size_t pos, t_str_info token, t_str_info replace);

//expand_tilde.c
t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos);

//expand_var.c
t_error	ft_expand_var(char **input, t_hashtable *symtab, size_t *pos, t_info *info);

#endif