/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 15:56:44 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"

__sig_atomic_t	g_status;

int	main(int argc, char **argv)
{
	t_data	data;
	char	*input;
	t_err	err;

	(void)argc;
	ft_startup(&data, argv[0]);
	while (data.loop)
	{
		ft_envp_create(data.env_table, &data.envp);
		ft_create_prompts(&data);
		ft_signal_setup(SIGINT, SIG_STD);
		if (isatty(fileno(stdin)))
			input = readline(data.prompt1);
		else
		{
			input = get_next_line(fileno(stdin));
			input = ft_strtrim(input, "\n");
		}
		ft_signal_setup(SIGINT, SIG_IGNORE);
		if (!input)
			break ;
		if (!ft_isempty_str(input))
		{
			add_history(input);
			err = ft_handle_input(input, &data);
		}
		ft_clean_after_loop(input, &data);
	}
	ft_hashtable_destroy(data.env_table);
	ft_buf_destroy(&data.buf);
	exit(g_status);
}
