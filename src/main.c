/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/23 10:48:34 by gwolf            ###   ########.fr       */
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
	if (ft_env_setup(&data.env_table, argv[0], &data.buf) != SUCCESS)
		printf("NO\n");
	data.loop = true;
	while (data.loop)
	{
		err = ft_envp_create(data.env_table, &data.envp);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		err = ft_prompt_create(data.env_table, &data.prompt1, "PS1", PS1_STD);
		if (err != SUCCESS)
			perror("Standard prompt creation failed.");
		err = ft_prompt_create(data.env_table, &data.prompt2, "PS2", PS2_STD);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		ft_signal_setup(SIGINT, SIG_STD);
		if (err != SUCCESS)
			ft_exit_failure(&data, err);
		if (isatty(fileno(stdin)))
			input = readline(data.prompt1);
		else
		{
			input = get_next_line(fileno(stdin));
			input = ft_strtrim(input, "\n");
		}
		if (!input)
			break ;
		if (!ft_isempty_str(input))
		{
			add_history(input);
			ft_signal_setup(SIGINT, SIG_IGNORE);
			if (err != SUCCESS)
				ft_exit_failure(&data, err);
			err = ft_handle_input(input, &data);
		}
		free(input);
		free(data.prompt1);
		free(data.prompt2);
		ft_envp_destroy(&data.envp);
	}
	ft_hashtable_destroy(data.env_table);
	ft_buf_destroy(&data.buf);
	exit(g_status);
}
