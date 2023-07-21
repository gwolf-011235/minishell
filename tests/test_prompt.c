/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:11:47 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 13:59:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_prompt(void)
{
	t_hashtable	*sym_tab;
	char		*prompt;

	sym_tab = ft_hashtable_create(100, ft_hash_fnv1);
	prompt = NULL;
	printf("\nNo var PS1 or PS2\n");
	{
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("This is empty prompt PS1: %s\n", prompt);
		free(prompt);
		ft_prompt_create(sym_tab, &prompt, "PS2", PS2_STD);
		printf("This is empty prompt PS2: %s\n", prompt);
		free(prompt);
	}
	printf("\nSimple var for PS1 and PS2\n");
	{
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=I'm testboy"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("This is prompt PS1: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("PS2=Be gentle!"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS2", PS2_STD);
		printf("This is prompt PS2: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS2", 3);
		free(prompt);
	}
	printf("\nConversion \\h\n");
	{
		printf("No SESSION_MANAGER\n");
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=\\h"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
		free(prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("SESSION_MANAGER=local/hello:"), 15);
		printf("After insert of SESSION_MANAGER\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
		free(prompt);
		ft_hashtable_swap(sym_tab, ft_strdup("SESSION_MANAGER=bye.thisis:local/nonono.maybe:"), 15);
		printf("After swap of SESSION_MANAGER\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\h: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
	}
	printf("\nConversion \\u\n");
	{
		printf("No USER\n");
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=\\u"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\u: %s\n", prompt);
		free(prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("USER=Testboiii"), 4);
		printf("After insert of USER\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\u: %s\n", prompt);
		free(prompt);
		ft_hashtable_swap(sym_tab, ft_strdup("USER="), 4);
		printf("Empty USER\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\u: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
	}
	printf("\nConversion \\w\n");
	{
		printf("No PWD\n");
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=\\w"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\w: %s\n", prompt);
		free(prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("PWD=nfs/homes/test"), 3);
		printf("After insert of PWD but no HOME\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\w: %s\n", prompt);
		free(prompt);
		ft_hashtable_insert(sym_tab, ft_strdup("HOME=nfs/homes"), 4);
		printf("After insert of PWD and HOME\n");
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=\\w: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
	}
	printf("\nWrong PS1 string - single backslash\n");
	{
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=bad\\"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=bad\\: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
	}
	printf("\nWrong PS1 string - not supported\n");
	{
		ft_hashtable_insert(sym_tab, ft_strdup("PS1=no no\\z"), 3);
		ft_prompt_create(sym_tab, &prompt, "PS1", PS1_STD);
		printf("PS1=no no\\z: %s\n", prompt);
		ft_hashtable_delete(sym_tab, "PS1", 3);
		free(prompt);
	}
	ft_hashtable_destroy(sym_tab);


}