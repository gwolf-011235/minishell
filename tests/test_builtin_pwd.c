/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:10:43 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 22:18:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

extern t_data	g_data;

void	test_builtin_pwd(void)
{
	printf(YELLOW"**\tTEST BUILTIN CD\t**\n\n"RESET);
	test_setup_data();
	printf("TEST: normal\n");
	ft_pwd();
	printf("\n");
	ft_hashtable_delete(g_data.env_table, "PWD", 3);
	printf("TEST: no $PWD\n");
	ft_pwd();
	printf("\n");
	test_teardown_data();

}