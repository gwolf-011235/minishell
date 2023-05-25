/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 15:08:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * @brief Overarching header
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

# include "libft.h"
# include "hashtable.h"
# include "minishell_error.h"

# define HASHTABLE_SIZE 10
# define MAX_SHLVL 10

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

/**
 * @brief Overarching struct to hold all necessarry data.
 *
 * This struct will be passed around to give access to several needed
 * var in different programm stages.
 * @param env_table Pointer to the env hashtable.
 * @param checks Struct with some flags.
 * @param err Can hold an error code if data is available - maybe del.
 */
typedef struct s_data {
	t_hashtable	*env_table;
	t_checks	checks;
	t_error		err;
}	t_data;

/**
 * @brief Global environ which holds the passed environment.
 *
 * More portable solution than the usage of char *envp.
 */
extern char	**environ;

//exit_failure.c
void	ft_exit_failure(t_data *data, t_error exit_code);

//init.c
t_error	ft_env_setup(t_data *data);
t_error	ft_env_import(t_data *data);
t_error	ft_env_insert_pwd(t_data *data);
t_error	ft_env_insert_shlvl(t_data *data);

//pwd.c
t_error	ft_create_pwd_value(char **pwd_value);
t_error	ft_create_pwd_env_str(char **pwd);

//shlvl.c
t_error	ft_create_shlvl_env_str(char **shlvl);
t_error	ft_increment_shlvl(t_data *data);


#endif