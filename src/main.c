/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 16:29:11 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"

__sig_atomic_t	g_status;

void	ft_read_input(char **input, char *prompt1)
{
	if (isatty(STDIN_FILENO))
		*input = readline(prompt1);
	else
		*input = get_next_line(STDIN_FILENO);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*input;

	(void)argc;
	ft_startup(&data, argv[0]);
	while (data.loop)
	{
		ft_envp_create(data.env_table, &data.envp);
		ft_create_prompts(&data);
		ft_signal_setup(SIGINT, SIG_STD);
		input = NULL;
		ft_read_input(&input, data.prompt1);
		ft_signal_setup(SIGINT, SIG_IGNORE);
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", 1);
			break ;
		}
		if (!ft_isempty_str(input))
			ft_handle_input(input, &data);
		ft_clean_after_loop(input, &data);
	}
	ft_hashtable_destroy(data.env_table);
	ft_buf_destroy(&data.buf);
	exit(g_status);
}
