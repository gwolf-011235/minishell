/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:17:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 18:36:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*symtab;
extern char			**envp;

void	test_env_envp_two(void)
{
	size_t		i;

	ft_hashtable_insert(symtab, "TEST=This is a value", 4);
	ft_hashtable_insert(symtab, "TEST2=Another value", 5);
	ft_envp_create(symtab, &envp);
	printf("This is envp[0]: %p\n", envp[0]);
	printf("This is envp[1]: %p\n", envp[1]);
	printf("This is envp[2]: %p\n", envp[2]);
	i = 0;
	while (envp[i])
	{
		printf("This is %lu. symbol: %s\n", i + 1, envp[i]);
		i++;
	}
	ft_envp_destroy(&envp);

}

void	test_env_envp_empty(void)
{
	ft_envp_create(symtab, &envp);
	printf("This is envp[0]: %p\n", envp[0]);
	ft_envp_destroy(&envp);
}

void	test_env_envp(void)
{
	symtab = ft_hashtable_create(10, ft_hash_fnv1);
	//test_env_envp_empty();
	test_env_envp_two();
}
