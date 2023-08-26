/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_cleanup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:33:17 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 20:20:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_CLEANUP_H
# define MOD_CLEANUP_H

/* ====== Includes ====== */

# include <stdbool.h>
# include <readline/history.h>
# include "minishell_error.h"
# include "libft.h"
# include "minishell_struct.h"

/* ====== Functions ====== */
void	ft_free_str_arr(char **arr);
void	ft_clean_after_loop(char **input, t_data *data);
void	ft_clean_on_exit(char **input, t_data *data);

//from MOD ENV
t_err	ft_envp_destroy(char ***envp);

#endif
