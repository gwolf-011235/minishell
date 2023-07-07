/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:11:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/07 12:10:03 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_ENVP_H
# define ENV_ENVP_H

# include <stdint.h>

# include "minishell_error.h"
# include "hashtable.h"

t_error	ft_envp_create(t_hashtable *ht, char ***envp);
t_error	ft_envp_destroy(char ***envp);

#endif