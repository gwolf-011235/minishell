/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:41:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 19:58:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_ENV_H
# define MOD_ENV_H

# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "minishell_config.h"
# include "hashtable.h"

/**
 * @brief Global environ which holds the passed environment.
 *
 * More portable solution than the usage of char *envp.
 */
extern char	**environ;

# define MAX "minishell: warning: shell level (%d) too high, resetting to 1\n"

//env_setup.c
t_err	ft_env_setup(t_hashtable **env_table, char *argv_zero);
t_err	ft_import_environ(t_hashtable *env_table);
t_err	ft_copy_environ_str(t_hashtable *env_table, char *environ_str);
t_err	ft_insert_env_prompt(t_hashtable *env_table, char opt);
t_err	ft_insert_env_zero(t_hashtable *env_table, char *argv_zero);

//env_pwd.c
t_err	ft_create_pwd_value(char **pwd_value);
t_err	ft_create_env_pwd(char **pwd);
t_err	ft_insert_env_pwd(t_hashtable *env_table);

//env_shlvl.c
t_err	ft_create_env_shlvl(char **shlvl, int val);
t_err	ft_increment_shlvl(t_hashtable *env_table);
t_err	ft_insert_env_shlvl(t_hashtable *env_table);

//env_pid.c
t_err	ft_get_pid_value(int *pid);
t_err	ft_create_env_pid(char **env_pid);
t_err	ft_insert_env_pid(t_hashtable *env_table);

//env_envp.c
t_err	ft_envp_fill(t_hashtable *ht, char **envp, bool all);
t_err	ft_envp_create(t_hashtable *ht, char ***envp);
t_err	ft_envp_create_all(t_hashtable *ht, char ***envp);
t_err	ft_envp_destroy(char ***envp);

//Import from mod_builtin
t_err	ft_get_env_keylen(char *str, size_t *len);

#endif
