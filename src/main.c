/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 16:55:06 by gwolf            ###   ########.fr       */
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
	t_data	data;
	char	*input;
	t_err	err;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	err = ft_signal_setup(SIGQUIT, SIG_IGNORE);
	if (err != SUCCESS)
		ft_exit_failure(&data, err);
	if (ft_env_setup(&data.env_table) != SUCCESS)
		printf("NO\n");
	ft_envp_create(data.env_table, &data.envp);
	//ft_hashtable_insert(data->env_table, "PS1=\\u@\\h:\\w$ ", 3);
	data.loop = true;
	while (data.loop)
	{
		err = ft_prompt_create(data.env_table, &data.prompt1, "PS1", PS1_STD);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		err = ft_prompt_create(data.env_table, &data.prompt2, "PS2", PS2_STD);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		err = ft_signal_setup(SIGINT, SIG_STD);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		input = readline(data.prompt1);
		if (!input)
			break ;
		add_history(input);
		err = ft_signal_setup(SIGINT, SIG_IGNORE);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		err = ft_handle_input(input, &data);
		free(input);
		free(data.prompt1);
		free(data.prompt2);
	}
	return (0);
}
