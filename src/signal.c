/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 16:26:45 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_signal.h"

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

void	ft_sighandler_weird_shit(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		//printf("yo waddup");
		//ft_putchar_fd('\n', 2);
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
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		//close(0);
	}
}

t_err	ft_signal_setup(t_state state)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (state == SIG_STD || state == SIG_INIT)
		sa.sa_handler = ft_sighandler_std;
	else if (state == SIG_HEREDOC)
		sa.sa_handler = ft_sighandler_heredoc;
	else if (state == SIG_WSHIT)
		sa.sa_handler = ft_sighandler_weird_shit;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (ERR_SIGNAL);
	if (state == SIG_INIT)
	{
		if (sigaction(SIGQUIT, &sa, NULL) != 0)
			return (ERR_SIGNAL);
	}
	return (SUCCESS);
}
