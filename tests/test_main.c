/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:40:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/18 03:15:51 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_data		g_data;
char		*g_string;
t_hashtable	*g_symtab;
char		**g_envp;
t_info		g_info;
int			g_err_count;

int	main(void)
{
	//test_hashtable();
	//test_replace_token();
	//test_prompt();
	//test_check_syntax();
	//test_env_envp();
	test_expand();
	//test_lexer();
	return (0);
}
