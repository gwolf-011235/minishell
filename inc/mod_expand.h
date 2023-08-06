/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/06 18:39:01 by gwolf            ###   ########.fr       */
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

//expand.c
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_hashtable *env_table);
t_err	ft_handle_heredoc(t_tkn_list **list);
t_err	ft_handle_redirect(t_tkn_list **list, t_hashtable *symtab);
t_err	ft_handle_arg(t_tkn_list **list, t_hashtable *symtab);

//expand_expander.c
t_err	ft_expander(char **str, t_hashtable *symtab, bool *exec);
t_err	ft_skip_single_quote(t_track *input);
t_err	ft_skip_double_quote(t_track *input, bool *in_double_quotes);

//expand_tilde.c
t_err	ft_expand_tilde(t_track *input, t_hashtable *symtab);
t_err	ft_get_tilde_replace(t_str token, t_hashtable *symtab, t_str *replace, size_t *pos);
t_err	ft_get_tilde_token(t_track *input, t_str *token);

//expand_var.c
t_err	ft_expand_var(t_track *input, t_hashtable *symtab, bool quotes, bool *exec);
t_err	ft_special_var(t_str *token, t_str *replace);
t_err	ft_get_var_token(t_track *input, t_str *token, bool quotes);
t_err	ft_get_var_replace(t_str token, t_hashtable *symtab, t_str *replace);

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

//expand_quote_removal.c
t_err	ft_quote_removal(char *str);
t_err	ft_rm_single_quote(t_track *input);
t_err	ft_rm_double_quote(t_track *input, bool *in_double_quotes);

//expand_utils.c
t_err	ft_init_tracker(t_track *input, char *str);
t_err	ft_move_tracker(t_track *input);
t_err	ft_eat_char(char *input, size_t pos);
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace);

#endif