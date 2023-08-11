/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/11 10:05:10 by sqiu             ###   ########.fr       */
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

//MODULE ENV
t_err	ft_env_setup(t_hashtable **env_table);
t_err	ft_envp_create(t_hashtable *ht, char ***envp);

//MODULE PROMPT
t_err	ft_prompt_create(t_hashtable *sym_tab,
			char **prompt, char *ps, char *std);

// MODULE HANDLE INPUT
t_err	ft_handle_input(char *input, t_data *data);

//exit_failure.c
void	ft_exit_failure(t_data *data, t_err exit_code);

#endif
