/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 18:48:34 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"

__sig_atomic_t	g_status;

/**
 * @brief Prepares each new loop of shell prompt.
 * 
 * @param data 		Overarching struct containing env.
 * @param input 	Input string formerly freed to be initiated to NULL.
 */
void	ft_prep_new_loop(t_data *data, char **input)
{
	ft_signal_setup(SIGQUIT, SIG_IGNORE);
	ft_envp_create(data->env_table, &data->envp);
	ft_create_prompts(data);
	*input = NULL;
}

/**
 * @brief Check if input is coming from tty and use appropriate function.
 *
 * If isatty() of stdin, stdout and stderr we have a terminal > use readline.
 * Else use get_next_line().
 * Check if atleast isatty() stdin > then print prompt.
 * If get_next_line() returns a line, eliminate last newline with '\0'.
 * If g_status == 2 (syntax error) and get_next_line() would be called (no tty)
 * then return > shell script has syntax error.
 * @param input		Where to save input.
 * @param prompt1	PS1 to display with readline.
 * @param state		State for signalhandler (std or heredoc).
 */
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
		if (g_status == 2)
			return ;
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
		ft_clean_after_loop(&input, &data);
	}
	ft_clean_on_exit(&input, &data);
	exit(g_status);
}
