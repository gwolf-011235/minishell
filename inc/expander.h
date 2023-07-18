/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/18 02:06:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "minishell_error.h"
# include "hashtable.h"
# include "ft_string.h"

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
t_error	ft_expand_tkn_lst(t_tkn_list *list, t_data *data);

//expand_tilde.c
t_error	ft_expand_tilde(t_track *input, t_hashtable *symtab);

//expand_var.c
t_error	ft_expand_var(t_track *input, t_hashtable *symtab, t_info *info, bool quotes);

//expand_utils.c
t_error	ft_insert_replace(t_track *input, t_str token, t_str replace);
t_error	ft_eat_char(char *input, size_t pos);
t_error	ft_handle_single_quote(t_track *input);
t_error	ft_handle_double_quote(t_track *input, bool *in_double_quotes);

#endif