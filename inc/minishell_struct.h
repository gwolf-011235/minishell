/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:38:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/28 13:01:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <stddef.h>

# include "hashtable.h"
# include "minishell_error.h"

/* ====== STRUCTS ====== */

/**
 * @brief Flags which can be set to store some info.
 *
 * In this struct some flags can be stored to be set and then be checked
 * later on.
 * @param no_env Environ was empty.
 * @param no_pwd Environ wasn't empty but didn't contain a PWD variable.
 */
typedef struct s_checks {
	bool	no_env;
	bool	no_pwd;
}	t_checks;

typedef struct s_info {
	size_t	ret_code;
	char	*shell_name;
}	t_info;

/**
 * @brief Overarching struct to hold all necessarry data.
 *
 * This struct will be passed around to give access to several needed
 * var in different programm stages.
 * @param env_table Pointer to the env hashtable.
 * @param checks Struct with some flags.
 * @param err Can hold an error code if data is available - maybe del.
 * @param token Struct containing the current token and its size.
 * @param lst_head Pointer to first node of token list.
 * @param cmds List of structs containing simple commands.
 */
typedef struct s_data {
	t_hashtable	*env_table;
	t_checks	checks;
	t_err		err;
	//t_cmd		*cmds;
	char		*prompt1;
	char		*prompt2;
	t_info		info;
}	t_data;

#endif