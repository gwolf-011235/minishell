/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:11:47 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/06 15:13:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_prompt(void)
{
	t_hashtable	*sym_tab;
	char		*prompt;

	sym_tab = ft_hashtable_create(100, ft_hash_fnv1);
	prompt = NULL;
	//no var PS1 or PS2
	{
		ft_create_prompt(sym_tab, &prompt, "PS1", PS1_STD);
		printf("This is empty prompt PS1: %s\n", prompt);
		free(prompt);
		ft_create_prompt(sym_tab, &prompt, "PS2", PS2_STD);
		printf("This is empty prompt PS2: %s\n", prompt);
		free(prompt);
	}
	//simple var PS1 and PS2
	{
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=I'm testboy"), 3);
		ft_create_prompt(sym_tab, &prompt, "PS1", PS1_STD);
		printf("This is prompt PS1: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		ft_hashtable_insert(sym_tab, ft_strdup("PS2=Be gentle!"), 3);
		ft_create_prompt(sym_tab, &prompt, "PS2", PS2_STD);
		printf("This is prompt PS2: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS2", 3);
	}
	//using the conversions \h - \u - \w - \n
	{
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=\\h"), 3);
		ft_create_prompt(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("SESSION_MANAGER=local/hello:"), 15);
		printf("After insert of SESSION_MANAGER\n");
		ft_create_prompt(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
		ft_hashtable_swap(sym_tab, ft_strdup("SESSION_MANAGER=bye"), 15);
		printf("After swap of SESSION_MANAGER\n");
		ft_create_prompt(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
	}


}