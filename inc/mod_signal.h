/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/12 03:56:41 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_SIGNAL_H
# define MOD_SIGNAL_H

# define _XOPEN_SOURCE 700

# include <signal.h>
# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/ioctl.h>

# include "minishell_error.h"
# include "libft.h"

extern __sig_atomic_t	g_status;

typedef enum e_state {
	SIG_INIT,
	SIG_STD,
	SIG_HEREDOC,
	SIG_WSHIT
}	t_state;

t_err	ft_signal_setup(t_state state);
void	ft_sighandler_std(int signum);
void	ft_sighandler_heredoc(int signum);

#endif