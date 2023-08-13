/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/13 20:10:16 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"
#include "mod_lexer.h"
#include "mod_signal.h"
#include "mod_env.h"

__sig_atomic_t	g_status;

int	main(int argc, char **argv)
{
	t_data	data;
	char	*input;
	t_err	err;	

	(void)argc;
	(void)argv;
	ft_signal_setup(SIGINT, SIG_IGNORE);
	ft_signal_setup(SIGQUIT, SIG_IGNORE);
	if (ft_env_setup(&data.env_table) != SUCCESS)
		printf("NO\n");
	//ft_hashtable_insert(data->env_table, "PS1=\\u@\\h:\\w$ ", 3);
	while (1)
	{
		err = ft_envp_create(data.env_table, &data.envp);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		err = ft_prompt_create(data.env_table, &data.prompt1, "PS1", PS1_STD);
		if (err != SUCCESS)
			perror("Standard prompt creation failed.");
		err = ft_prompt_create(data.env_table, &data.prompt2, "PS2", PS2_STD);
		if (err != SUCCESS)
			perror("Heredoc prompt creation failed.");
		ft_signal_setup(SIGINT, SIG_STD);
		input = readline(data.prompt1);
		if (!input)
			break ;
		add_history(input);
		ft_signal_setup(SIGINT, SIG_IGNORE);
		err = ft_handle_input(input, &data);
		free(input);
		free(data.prompt1);
		free(data.prompt2);
		ft_envp_destroy(&data.envp);
	}
	return (0);
}
