/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:57:23 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/13 18:11:47 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

void	ft_err_signal(int signum, __sighandler_t sighodl)
{
	errno = 0;
	if (signal(signum, sighodl) == SIG_ERR)
		perror("Could not assign signal handler :( ");
}
