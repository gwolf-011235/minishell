/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:38:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 10:32:19 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <stddef.h>

# include "hashtable.h"
# include "minishell_error.h"

/* ====== STRUCTS ====== */

/**
 * @brief Overarching struct to hold all necessarry data.
 *
 * This struct will be passed around to give access to several needed
 * var in different programm stages.
 * @param env_table Pointer to the env hashtable.
 * @param envp String array containing the environment.
 * @param checks Struct with some flags.
 * @param err Can hold an error code if data is available - maybe del.
 * @param token Struct containing the current token and its size.
 * @param lst_head Pointer to first node of token list.
 * @param cmds List of structs containing simple commands.
 */
typedef struct s_data {
	t_hashtable	*env_table;
	char		**envp;
	t_err		err;
	char		*prompt1;
	char		*prompt2;
	bool		loop;
}	t_data;

#endif
