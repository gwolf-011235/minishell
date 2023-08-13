/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/13 18:11:55 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal.c
 * @brief Functions to handle signals.
 */

#include "mod_signal.h"

/**
 * @brief Standard signal handler for readline.
 * 
 * When SIGINT is received, a newline is printed.
 * Readline goes to the newline and display an
 * empty prompt.
 * @param signum 	Signal received.
 */
void	ft_sighandler_std(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief Standard signal handler for readline inside of heredocs.
 * 
 * When SIGINT is received, a newline is faked.
 * Readline goes to the newline.
 * @param signum 	Signal received.
 */
void	ft_sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

/**
 * @brief Signal handler that does nothing.
 * 
 * @param signum 	Signal received.
 */
void	ft_sighandler_ignore(int signum)
{
	(void)signum;
}

/**
 * @brief Assign signalhandler to signal 'signum'.
 * 
 * @param signum 	Signal received.
 * @param state 	Indicator of signal handler.
 */
void	ft_signal_setup(int signum, t_state state)
{
	struct sigaction	sa;

	errno = 0;
	sigemptyset(&sa.sa_mask);
	if (state == SIG_STD)
		sa.sa_handler = ft_sighandler_std;
	else if (state == SIG_HEREDOC)
		sa.sa_handler = ft_sighandler_heredoc;
	else if (state == SIG_IGNORE)
		sa.sa_handler = ft_sighandler_ignore;
	if (sigaction(signum, &sa, NULL) != 0)
		perror("Could not assign signal handler :( ");
}
