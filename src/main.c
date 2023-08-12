/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 03:13:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"
#include "mod_lexer.h"
#include "mod_signal.h"
/* #include "lexer_list.h"
#include "lexer_tok_utils.h" */

__sig_atomic_t	g_status;

int	main(int argc, char **argv)
{
	t_data		*data;
	char		*input;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_signal_setup(SIG_INIT);
	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	if (ft_env_setup(&data->env_table) != SUCCESS)
		printf("NO\n");
	ft_envp_create(data->env_table, &data->envp);
	//ft_hashtable_insert(data->env_table, "PS1=\\u@\\h:\\w$ ", 3);
	while (1)
	{
		ft_signal_setup(SIG_STD);
		data->err = ft_prompt_create(data->env_table, &data->prompt1, "PS1", PS1_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		data->err = ft_prompt_create(data->env_table, &data->prompt2, "PS2", PS2_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		input = readline(data->prompt1);
		if (!input)
			break ;
		add_history(input);
		data->err = ft_handle_input(input, data);
/* 		if (data->err != SUCCESS && data->err != ERR_NO_INPUT)
			ft_exit_failure(data, data->err);
		//do stuff */
		free(input);
		free(data->prompt1);
		free(data->prompt2);
	}
	return (0);
}
