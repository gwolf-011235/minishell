/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 02:12:27 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_signal.h"

void	ft_sighandler_std(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	ft_sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		close(0);
		ft_putchar_fd('\n', 2);
	}
}

t_err	ft_signal_setup_std(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_sighandler_std;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (ERR_SIGNAL);
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (ERR_SIGNAL);
	return (SUCCESS);
}

t_err	ft_signal_setup_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_sighandler_heredoc;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (ERR_SIGNAL);
	return (SUCCESS);
}
