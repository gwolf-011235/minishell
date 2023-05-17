/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/17 17:58:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int			i;
	char		*env_ptr;
	t_hashtable	*ht;

	i = 0;
	env_ptr = environ[i];
	ht = ft_hashtable_create(128, ft_hash_fnv1);
	size_t keylen = ft_strchr(env_ptr, '=') - env_ptr;
	ft_hashtable_insert(ht, env_ptr, keylen);
	ft_hashtable_print(ht);
}