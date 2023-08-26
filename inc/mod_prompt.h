/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_prompt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:45:35 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 20:03:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_PROMPT_H
# define MOD_PROMPT_H

# include <fcntl.h>

# include "minishell_config.h"
# include "minishell_utils.h"
# include "hashtable.h"
# include "libft.h"

# define PROMPT_EXPAND_SUPPORTED "hnurw"
# define PROMPT_EXPAND_EMPTY "\\"
# define PROMPT_EXPAND_H "\\h"
# define PROMPT_EXPAND_N "\\n"
# define PROMPT_EXPAND_U "\\u"
# define PROMPT_EXPAND_R "\\r"
# define PROMPT_EXPAND_W "\\w"

typedef t_err		(*t_replace_ptr)(char **replacement, t_hashtable *sym_tab);

//prompt_create.c
t_err	ft_prompt_create(t_hashtable *sym_tab,
			char **prompt, char *ps, char *std);
t_err	ft_expand_prompt_str(char **prompt, t_hashtable *sym_tab);
t_err	ft_search_token(const char *ps_string, char **token);
t_err	ft_get_token(char **token, unsigned char target);
t_err	ft_get_replace(char **replacement, unsigned char target,
			t_hashtable *sym_tab);

//prompt_replace_token.c
void	ft_calc_replace_len(const char *str, const char *token,
			const char *replacement, size_t *expanded_len);
t_err	ft_expand_str(char **expanded_str, const char *str,
			const char *token, const char *replacement);
t_err	ft_replace_token(char **str, const char *token,
			const char *replacement);

//prompt_replace_small.c
t_err	ft_replace_n(char **replacement, t_hashtable *sym_tab);
t_err	ft_replace_r(char **replacement, t_hashtable *sym_tab);
t_err	ft_replace_not_found(char **replacement);
t_err	ft_replace_empty(char **replacement, t_hashtable *sym_tab);

//prompt_replace_h.c
t_err	ft_replace_h(char **replacement, t_hashtable *sym_tab);
t_err	ft_retrieve_hostname(char **replacement);

//prompt_replace_u.c
t_err	ft_replace_u(char **replacement, t_hashtable *sym_tab);

//prompt_replace_w.c
t_err	ft_replace_w(char **replacement, t_hashtable *sym_tab);
t_err	ft_replace_tilde(char **replacement, t_hashtable *sym_tab);

#endif