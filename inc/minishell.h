/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/02 16:56:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "libft.h"
# include "minishell_error.h"

# define PS1_STD "$ "
# define PS2_STD "> "
# define UNKNOWN "UNKNOWN"

# define PROMPT_EXPAND_SUPPORTED "hnurw"
# define PROPMT_EXPAND_EMPTY "\\"
# define PROMPT_EXPAND_H "\\h"
# define PROMPT_EXPAND_N "\\n"
# define PROMPT_EXPAND_U "\\u"
# define PROMPT_EXPAND_R "\\r"
# define PROMPT_EXPAND_W "\\w"

typedef	int t_hashtable;
typedef struct s_env_var {
	char	*value;
}	t_env_var;

typedef t_error	(*t_replace_ptr)(char **replacement, t_hashtable sym_tab);

//memory.c
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size);

//replace_token.c
t_error	ft_calc_replace_len(const char *str, const char *token,
			const char *replacement, size_t *expanded_len);
t_error	ft_replace_token(char **str, const char *token,
			const char *replacement);

//ft_string.c
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);

//prompt.c
t_error	ft_create_prompt(t_hashtable sym_tab,
			char **prompt, char *ps, char *std);

//prompt_replace_small.c
t_error	ft_prompt_replace_n(char **replacement, t_hashtable sym_tab);
t_error	ft_prompt_replace_r(char **replacement, t_hashtable sym_tab);
t_error	ft_prompt_replace_not_found(char **replacement);
t_error	ft_prompt_replace_empty(char **replacement, t_hashtable sym_tab);

//prompt_replace_h.c
t_error	ft_prompt_replace_h(char **replacement, t_hashtable sym_tab);
t_error	ft_prompt_create_hostname(char **replacement, const char *str);

//prompt_replace_u.c
t_error	ft_prompt_replace_u(char **replacement, t_hashtable sym_tab);

//prompt_replace_w.c
t_error	ft_prompt_replace_w(char **replacement, t_hashtable sym_tab);
# include "hashtable.h"

extern char	**environ;

#endif