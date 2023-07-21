/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 17:46:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_signal.h"

void	ft_signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	ft_putnbr_fd(info->si_pid, 1);
	ft_putendl_fd("SIGNAL RECEIVED\n", 1);

}

t_err	ft_signal_setup(void)
{
	struct sigaction	sa;
	int					ret;

	sa.sa_sigaction = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGINT, &sa, NULL);
	if (ret > 0)
		return (ERR_SIGNAL);
	return (SUCCESS);
}
