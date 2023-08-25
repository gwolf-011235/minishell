/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 15:56:18 by gwolf            ###   ########.fr       */
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
# include "mod_signal.h"

//init.c
void	ft_startup(t_data *data, char *argv_zero);
void	ft_init_data(t_data *data);

//MODULE ENV
void	ft_env_setup(t_hashtable *env_table, char *argv_zero, t_buf *buf);
void	ft_envp_create(t_hashtable *ht, char ***envp);

//MODULE PROMPT
void	ft_create_prompts(t_data *data);
t_err	ft_prompt_create(t_hashtable *sym_tab,
			char **prompt, char *ps, char *std);

// MODULE HANDLE INPUT
t_err	ft_handle_input(char *input, t_data *data);

//cleanup.c
void	ft_clean_after_loop(char *input, t_data *data);

//exit_failure.c
t_err	ft_exit_failure(t_data *data, t_err exit_code);

#endif
