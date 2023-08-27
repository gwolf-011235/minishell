* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:20 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 17:32:34by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_BUILTIN_H
# define MOD_BUILTIN_H

# include "hashtable.h"
# include "buffer.h"
# include "minishell_utils.h"

extern __sig_atomic_t	g_status;

//IMPORT MOD_ENV
t_err	ft_create_pwd_value(t_buf *buf);
t_err	ft_create_env_pwd(char **pwd, t_buf *buf);
t_err	ft_envp_create_all(t_hashtable *ht, char ***envp);
t_err	ft_envp_destroy(char ***envp);

//utils.c
void	ft_get_array_size(char **array, size_t *size);
t_err	ft_get_env_keylen(char *str, size_t *len);
t_err	ft_update_env_var(t_hashtable *env_tab,
			char *env_str, size_t keylen, bool has_value);
void	ft_quicksort_strings(char **arr, int low, int high);
void	ft_eat_char2(char *str, size_t pos);

//error.c
void	ft_cd_error(t_err err, char *oldpwd);
t_err	ft_pwd_error(t_err err);
void	ft_export_error(t_err err, char *arg);
void	ft_exit_error(t_err err, char *arg);

//echo.c
void	ft_echo(char **argv);
void	ft_skip_n_flags(char **argv, size_t *i, bool *newline);
t_err	ft_write_args(char **argv, size_t *i);

//cd.c
void	ft_cd(char **argv, t_hashtable *env_tab, t_buf *buf);
t_err	ft_save_cur_pwd(char **oldpwd, t_hashtable *env_tab);
t_err	ft_redirect_path(t_hashtable *env_tab, char *name, t_buf *buf);
t_err	ft_change_dir(char *path, t_hashtable *env_tab, t_buf *buf, bool print);

//pwd.c
void	ft_pwd(t_buf *buf);

//export.c
void	ft_export(char **argv, t_hashtable *env_tab);
void	ft_print_env_sorted(t_hashtable *env_tab);
t_err	ft_pretty_print_envp(char **envp, size_t size);
t_err	ft_check_and_update_env(char *str, t_hashtable *env_tab, size_t keylen);
t_err	ft_concatenate(char *env_str, t_hashtable *env_tab, size_t keylen);

//unset.c
void	ft_unset(char **argv, t_hashtable *env_tab);

//env.c
void	ft_env(t_hashtable *env_tab);

//exit.c
void	ft_exit(char **argv, bool *loop);
t_err	ft_is_number(char *str);


#endif
