/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/22 17:18:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_SIGNAL_H
# define MOD_SIGNAL_H

# define _XOPEN_SOURCE 700

# include <signal.h>
# include <stddef.h>
# include <unistd.h>
# include <readline/readline.h>

# include "minishell_error.h"
# include "libft.h"

typedef enum e_state {
	SIG_STD,
	SIG_PARENT,
	SIG_CHILD,
	SIG_HEREDOC
}	t_state;

t_err	ft_signal_setup_std(void);
void	ft_sighandler_std(int signum);

#endif