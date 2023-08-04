/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_executor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:04:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/04 20:51:57 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_EXECUTOR_H
# define MOD_EXECUTOR_H

/* ====== Includes ====== */

# include "mod_handle_input.h"

/* ====== Structs ====== */

/* ====== Functions ====== */

void	ft_init_exec(t_cmd *cmd);
t_err	ft_execute_cmds(t_cmd *cmd, char **envp, char **paths);

void	ft_create_child(t_cmd *cmd, char **envp);

// utils
t_err	ft_check_cmd_access(char **args, char **cmd_paths);
t_err	ft_prefix_path(char **args, char **cmd_paths);
t_err	ft_get_path(char **envp, char ***paths);

#endif