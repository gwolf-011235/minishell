/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/05 17:48:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXPAND_H
# define MOD_EXPAND_H

# include "hashtable.h"
# include "minishell_struct.h"
# include "minishell_utils.h"
# include "mod_handle_input.h"
# include "mod_lexer.h"

# define BUF_SIZE 2048

extern __sig_atomic_t	g_status;

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
t_err	ft_expander(t_track *input, t_hashtable *symtab, bool *exec);
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace);
t_err	ft_skip_single_quote(t_track *input);
t_err	ft_skip_double_quote(t_track *input, bool *in_double_quotes);

//expand_tilde.c
t_err	ft_expand_tilde(t_track *input, t_hashtable *symtab);

//expand_var.c
t_err	ft_expand_var(t_track *input, t_hashtable *symtab, bool quotes);

//expand_quote_removal.c
t_err	ft_eat_char(char *input, size_t pos);
t_err	ft_rm_single_quote(t_track *input);
t_err	ft_rm_double_quote(t_track *input, bool *in_double_quotes);
t_err	ft_quote_removal(t_track input);

//expand_handler.c
t_err	ft_handle_heredoc(t_tkn_list **list);
t_err	ft_handle_redirect(t_tkn_list **list, t_hashtable *symtab);
t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab);

//expand_field_split.c
t_err	ft_field_split(t_tkn_list **list, size_t *words);
t_err	ft_quote_skip(const char *quote_start, size_t *i, char target);
t_err	ft_count_expand_words(char *str, size_t *words);
t_err	ft_split_node(t_tkn_list **lst_head, t_buf *buf);
t_err	ft_del_old_node(t_tkn_list **list, size_t *words);

//expand_field_split2.c
t_err	ft_partition_two(t_src *src, t_buf *buf);
t_err	ft_better_tokenise(t_src *src, t_tok *token, t_buf *buf);
t_err	ft_init_buf(t_buf *buf);

#endif