/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:11:47 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 20:07:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_hashtable	*g_symtab;

void	exec_prompt_create(char *name, char *env_str, int num, char *expect)
{
	char	*prompt;

	prompt = NULL;
	printf("TEST: %s\n", name);
	printf("VAR:\t%s\n", env_str);
	ft_hashtable_insert(g_symtab, ft_strdup(env_str), 3, true);
	if (num == 1)
		ft_prompt_create(g_symtab, &prompt, "PS1", PS1_STD);
	else
		ft_prompt_create(g_symtab, &prompt, "PS2", PS2_STD);
	printf("Prompt:\t%s\n\n", prompt);
	free(prompt);
	ft_hashtable_delete(g_symtab, env_str, 3);
}

void	test_prompt(void)
{
	g_symtab = ft_hashtable_create(100, ft_hash_fnv1);
	exec_prompt_create("No var for PS1", "NOVAR=", 1, "");
	exec_prompt_create("No var for PS2", "NOVAR=", 2, "");
	exec_prompt_create("Simple var for PS1", "PS1=I'm testboy ", 1, "I'm testboy ");
	exec_prompt_create("Simple var for PS2", "PS2=Be gentle ", 2, "Be gentle ");
	exec_prompt_create("\\h", "PS1=\\h ", 1, "hostname ");
	exec_prompt_create("\\u - no user", "PS1=\\u ", 1, "hostname ");
	ft_hashtable_insert(g_symtab, ft_strdup("USER=Testboiii"), 4, true);
	exec_prompt_create("\\u - with user", "PS1=\\u ", 1, "Testboiii ");
	ft_hashtable_swap(g_symtab, ft_strdup("USER="), 4, true);
	exec_prompt_create("\\u - empty user", "PS1=\\u ", 1, " ");
	exec_prompt_create("\\w - no PWD", "PS1=\\w ", 1, " ");
	ft_hashtable_insert(g_symtab, ft_strdup("PWD=nfs/homes/test"), 3, true);
	exec_prompt_create("\\w - PWD but no HOME", "PS1=\\w ", 1, " ");
	ft_hashtable_insert(g_symtab, ft_strdup("HOME=nfs/homes"), 4, true);
	exec_prompt_create("\\w - PWD and HOME", "PS1=\\w ", 1, " ");
	exec_prompt_create("Wrong string - single backslash", "PS1=bad\\ ", 1, " ");
	exec_prompt_create("Wrong string - not supported", "PS1=no \\z ", 1, " ");
	ft_hashtable_destroy(g_symtab);
}