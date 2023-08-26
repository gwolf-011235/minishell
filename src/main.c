/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 11:49:13 by gwolf            ###   ########.fr       */
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
	bool	tty;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		tty = true;
	else
		tty = false;
	if (tty)
		*input = readline(prompt1);
	else
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd(prompt1, 0);
		*input = get_next_line(STDIN_FILENO);
	}
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
			break ;
		else if (!ft_isempty_str(input))
			ft_handle_input(input, &data);
		ft_clean_after_loop(input, &data);
	}
	ft_clean_on_exit(&data);
	exit(g_status);
}
