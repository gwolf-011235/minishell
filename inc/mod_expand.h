/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/03 09:03:27 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXPAND_H
# define MOD_EXPAND_H

# include "hashtable.h"
# include "minishell_struct.h"
# include "minishell_utils.h"

/**
 * @brief String struct.
 *
 * Saves info about a string to save space.
 *
 * @param ptr Pointer to string.
 * @param len Len of string.
 */
typedef struct s_str_info {
	char	*ptr;
	size_t	len;
}	t_str;

/**
 * @brief Tracker struct.
 *
 * Track current position of input string.
 *
 * @param str Pointer to string.
 * @param pos Current position of the input string.
 */
typedef struct s_str_navi {
	char	*str;
	size_t	pos;
}	t_track;

//expander.c
t_err	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace);
t_err	ft_eat_char(char *input, size_t pos);

//expand_tilde.c
t_err	ft_expand_tilde(t_track *input, t_hashtable *symtab);

//expand_var.c
t_err	ft_expand_var(t_track *input, t_hashtable *symtab, t_info *info, bool quotes);

//expand_quote_removal.c
t_err	ft_eat_char(char *input, size_t pos);
t_err	ft_rm_single_quote(t_track *input);
t_err	ft_rm_double_quote(t_track *input, bool *in_double_quotes);


#endif