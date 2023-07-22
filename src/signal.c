/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 17:18:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_signal.h"

void	ft_sighandler_std(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

//maybe one for sigquit the other for sigint to use sigaction.
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
