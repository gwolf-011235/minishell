/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hashtable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:29:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/06 13:35:03 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_hashtable(void)
{
	t_hashtable	*sym_tab;
	t_env_var	*env_var;

	sym_tab = ft_hashtable_create(100, ft_hash_fnv1);

	ft_hashtable_insert(sym_tab, ft_strdup("TEST=Ima testing"), 4);
	env_var = ft_hashtable_lookup(sym_tab, "TEST", 4);
	if (env_var == NULL)
		printf("not found\n");
	else
		printf("TEST was found\n");
	ft_hashtable_delete(sym_tab, "TEST", 4);
}