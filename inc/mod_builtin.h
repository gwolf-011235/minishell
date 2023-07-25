/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:20 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 13:24:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_BUILTIN_H
# define MOD_BUILTIN_H

# include "hashtable.h"

//IMPORT MOD_ENV
t_err	ft_create_pwd_value(char **pwd_value);
t_err	ft_create_env_pwd(char **pwd);
t_err	ft_envp_create(t_hashtable *ht, char ***envp);
t_err	ft_envp_destroy(char ***envp);

//utils.c
t_err	ft_get_array_size(char **array, size_t *size);
t_err	ft_get_env_keylen(char *str, size_t *len);
t_err	ft_update_env_var(t_hashtable *env_tab, char *env_str, size_t keylen);
void	ft_swap(char **str1, char **str2);
void	ft_quicksort_strings(char **arr, int low, int high);

//error.c
t_err	ft_cd_error(t_err err, char *oldpwd, char *path);
t_err	ft_pwd_error(t_err err);
t_err	ft_export_error(t_err err, char *arg);

//echo.c
t_err	ft_skip_n_flags(char **argv, size_t *i, bool *newline);
t_err	ft_write_args(char **argv, size_t *i);
t_err	ft_echo(char **argv);

//cd.c
t_err	ft_change_dir(char *path, t_hashtable *env_tab, char *oldpwd);
t_err	ft_set_home_path(char **path, t_hashtable *env_tab);
t_err	ft_save_cur_pwd(char **oldpwd, t_hashtable *env_tab);
t_err	ft_cd(char **argv, t_hashtable *env_tab);

//pwd.c
t_err	ft_pwd(void);

//export.c
t_err	ft_check_and_update_env(char *str, t_hashtable *env_tab);
t_err	ft_pretty_print_envp(char **envp, size_t size);
t_err	ft_print_env_sorted(t_hashtable *env_tab);
t_err	ft_export(char **argv, t_hashtable *env_tab);

//unset.c
t_err	ft_unset(char **argv, t_hashtable *env_tab);

#endif