/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:57:20 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 20:03:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_BUILTIN_H
# define MOD_BUILTIN_H

# include "hashtable.h"

t_err	ft_get_array_size(char **array, size_t *size);
t_err	ft_cd(char **argv, t_hashtable *env_tab);


#endif