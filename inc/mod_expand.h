/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 21:51:24 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXPAND_H
# define MOD_EXPAND_H

# include "hashtable.h"
# include "minishell_struct.h"
# include "minishell_utils.h"
# include "mod_lexer.h"

extern __sig_atomic_t	g_status;

/**
 * @brief String struct.
 *
 * Saves info about a string to save space.
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
 * @param str Pointer to string.
 * @param pos Current position of the input string.
 * @param quoted True if string is currently inside double quotes.
 * @param last_expand_len Last expansion which was inserted.
 * @param found_quote At least one single or double quoted part was found
 */
typedef struct s_track {
	char	*str;
	size_t	pos;
	bool	quoted;
	int		last_expand_len;
	bool	found_quote;
	t_type	type;
}	t_track;

//expand.c
t_err	ft_expand_router(t_tkn_list **tmp, t_type type, t_hashtable *env_table,
			t_buf *buf);
t_err	ft_expand_err(t_tkn_list **lst_head);
t_err	ft_split_err(t_tok *token);

//expand_types.c
t_err	ft_expand_heredoc(t_tkn_list **list);
t_err	ft_expand_redirect(t_tkn_list **list, t_hashtable *symtab);
t_err	ft_expand_assign(t_tkn_list **list, t_hashtable *symtab);
t_err	ft_expand_arg(t_tkn_list **list, t_hashtable *symtab, t_buf *buf);

//expand_expander.c
t_err	ft_expander(t_track *input, t_hashtable *symtab, t_type type);
t_err	ft_rm_single_quote(t_track *input);
t_err	ft_rm_double_quote(t_track *input);
t_err	ft_expander_heredoc(char **str, t_hashtable *symtab);

//expand_tilde.c
t_err	ft_expand_tilde(t_track *input, t_hashtable *symtab);
t_err	ft_get_tilde_replace(t_str token, t_hashtable *symtab,
			t_str *replace, size_t *pos);
t_err	ft_get_tilde_var(t_track *input, t_str *token);

//expand_dollar.c
t_err	ft_expand_dollar(t_track *input, t_hashtable *symtab);
t_err	ft_special_dollar(t_str *token, t_str *replace, t_hashtable *symtab,
			char c);
t_err	ft_get_dollar_var(t_track *input, t_str *token);
t_err	ft_get_dollar_replace(t_str *token, t_hashtable *symtab,
			t_str *replace);

//expand_field_split.c
t_err	ft_field_split(t_track *input, t_tkn_list **list, t_buf *buf);
void	ft_count_expand_words(t_track *input, size_t *words,
			int last_expand_len);
t_err	ft_split_node(t_track *input, t_tkn_list **cur_node, t_buf *buf);
t_err	ft_tokenise_fs(t_src *src, t_tok *token, t_buf *buf, t_track *input);
t_err	ft_partition_fs(t_src *src, t_buf *buf);

//expand_utils.c
void	ft_init_tracker(t_track *input, char *str, t_type type);
t_err	ft_move_tracker(t_track *input);
void	ft_eat_char(t_track *input);
t_err	ft_insert_replace(t_track *input, t_str token, t_str replace);
t_err	ft_trim_single_word(t_track *input);

#endif
