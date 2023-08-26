/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/26 16:00:10 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"

__sig_atomic_t	g_status;

void	ft_prep_new_loop(t_data *data, char **input)
{
	ft_signal_setup(SIGQUIT, SIG_IGNORE);
	ft_envp_create(data->env_table, &data->envp);
	ft_create_prompts(data);
	*input = NULL;
}

void	ft_read_input(char **input, char *prompt1, t_state state)
{
	bool	tty;

	ft_signal_setup(SIGINT, state);
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
		if (*input)
		{
			if ((*input)[ft_strlen(*input) - 1] == '\n')
				(*input)[ft_strlen(*input) - 1] = '\0';
		}
	}
	ft_signal_setup(SIGINT, SIG_IGNORE);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*input;

	(void)argc;
	ft_startup(&data, argv[0]);
	while (data.loop)
	{
		ft_prep_new_loop(&data, &input);
		ft_read_input(&input, data.prompt1, SIG_STD);
		if (!input)
			break ;
		else if (!ft_isempty_str(input))
			ft_handle_input(input, &data);
		ft_clean_after_loop(input, &data);
	}
	ft_clean_on_exit(&data);
	exit(g_status);
}
