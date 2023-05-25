/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/02 17:02:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"

#ifdef TESTING
# define main not_main
#endif

int	main(int argc, char **argv)
{
	t_data *data;
	(void)argc;
	(void)argv;
	/*
	t_error	err;
	char 	*input;

	while (1)
	{
		err = ft_create_prompt(sym_tab, &prompt1, "PS1", PS1_STD);
		if (err != SUCCESS)
			//handle error
		err = ft_create_prompt(sym_tab, &prompt2, "PS2", PS2_STD);
		if (err != SUCCESS)
			//handle error
		input = readline(prompt1);
		if (!input)
			//handle no input e.g. break?
		add_history(input);
		//do stuff
		free(input);
		free(prompt1);
		free(prompt2);
	}
	*/
	return (0);
}