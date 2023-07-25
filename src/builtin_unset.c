/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:07:27 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 13:16:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_unset(char **argv, t_hashtable *env_tab)
{
	size_t		i;
	t_env_var	*target;

	i = 1;
	while (argv[i])
	{
		ft_hashtable_delete(env_tab, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (SUCCESS);
}
