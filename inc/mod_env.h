/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:41:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 08:20:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_ENV_H
# define MOD_ENV_H

# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "minishell_config.h"
# include "hashtable.h"
# include "buffer.h"

/**
 * @brief Global environ which holds the passed environment.
 *
 * More portable solution than the usage of char *envp.
 */
extern char	**environ;

//env_setup.c
void	ft_env_setup(t_hashtable *env_table, char *argv_zero, t_buf *buf);
void	ft_check_missing_env(t_hashtable *env_table, t_buf *buf);
void	ft_import_environ(t_hashtable *env_table);
t_err	ft_copy_environ_str(t_hashtable *env_table, char *environ_str);
t_err	ft_insert_env_prompt(t_hashtable *env_table, char *prompt);

//env_pwd.c
t_err	ft_create_pwd_value(t_buf *buf);
t_err	ft_create_env_pwd(char **pwd, t_buf *buf);
t_err	ft_insert_env_pwd(t_hashtable *env_table, t_buf *buf);

//env_shlvl.c
t_err	ft_create_env_shlvl(char **shlvl, int val);
t_err	ft_increment_shlvl(t_hashtable *env_table);
t_err	ft_insert_env_shlvl(t_hashtable *env_table);
void	ft_print_warning_shlvl(int new_val);

//env_special.c
t_err	ft_get_pid_value(pid_t *pid);
t_err	ft_create_env_pid(char **env_pid);
t_err	ft_insert_env_pid(t_hashtable *env_table);
t_err	ft_insert_env_zero(t_hashtable *env_table, char *argv_zero);
void	ft_set_special_params(t_hashtable *env_table, char *argv_zero);

//env_envp.c
t_err	ft_envp_fill(t_hashtable *ht, char **envp, bool all);
t_err	ft_envp_create(t_hashtable *ht, char ***envp);
t_err	ft_envp_create_all(t_hashtable *ht, char ***envp);
t_err	ft_envp_destroy(char ***envp);

//Import from mod_builtin
t_err	ft_get_env_keylen(char *str, size_t *len);

#endif
