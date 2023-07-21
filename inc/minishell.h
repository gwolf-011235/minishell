/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 13:36:50 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * @brief Overarching header
 */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ====== LIBRARIES ====== */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

# include "libft.h"
# include "minishell_error.h"
# include "hashtable.h"
# include "minishell_struct.h"
# include "minishell_config.h"


# define PROMPT_EXPAND_SUPPORTED "hnurw"
# define PROMPT_EXPAND_EMPTY "\\"
# define PROMPT_EXPAND_H "\\h"
# define PROMPT_EXPAND_N "\\n"
# define PROMPT_EXPAND_U "\\u"
# define PROMPT_EXPAND_R "\\r"
# define PROMPT_EXPAND_W "\\w"

typedef t_err		(*t_replace_ptr)(char **replacement, t_hashtable *sym_tab);

t_err	ft_env_setup(t_hashtable *env_table);

//exit_failure.c
void	ft_exit_failure(t_data *data, t_err exit_code);


//ft_memory.c
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size);

//replace_token.c
t_err	ft_calc_replace_len(const char *str, const char *token,
			const char *replacement, size_t *expanded_len);
t_err	ft_replace_token(char **str, const char *token,
			const char *replacement);

//prompt.c
t_err	ft_create_prompt(t_hashtable *sym_tab,
			char **prompt, char *ps, char *std);

//prompt_replace_small.c
t_err	ft_prompt_replace_n(char **replacement, t_hashtable *sym_tab);
t_err	ft_prompt_replace_r(char **replacement, t_hashtable *sym_tab);
t_err	ft_prompt_replace_not_found(char **replacement);
t_err	ft_prompt_replace_empty(char **replacement, t_hashtable *sym_tab);

//prompt_replace_h.c
t_err	ft_prompt_replace_h(char **replacement, t_hashtable *sym_tab);
t_err	ft_prompt_create_hostname(char **replacement, const char *str);

//prompt_replace_u.c
t_err	ft_prompt_replace_u(char **replacement, t_hashtable *sym_tab);

//prompt_replace_w.c
t_err	ft_prompt_replace_w(char **replacement, t_hashtable *sym_tab);

#endif