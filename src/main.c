/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/02 17:54:51 by gwolf            ###   ########.fr       */
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
	t_data	*data;
	char 	*input;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	if (ft_env_setup(data) != SUCCESS)
		printf("NO\n");
	while (1)
	{
		data->err = ft_create_prompt(data->env_table, &data->prompt1, "PS1", PS1_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		data->err = ft_create_prompt(data->env_table, &data->prompt2, "PS2", PS2_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		input = readline(data->prompt1);
		if (!input)
			break ;
		add_history(input);
		//do stuff
		free(input);
		free(data->prompt1);
		free(data->prompt2);
	}
	return (0);
}

