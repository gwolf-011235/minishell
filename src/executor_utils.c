/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:03:04 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/01 18:03:24 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_executor.h"

/* This function prefixes the appropriate path in front of the command,
if that is not already the case. To this aim, it rotates through all
command paths and checks whether the combination with the command is
correct via 'access'. If so, the command including its path is returned.
In case of failure to find a working path to the command NULL is returned. */

char	*ft_get_path(char *cmd, char **cmd_paths)
{
	char	*tmp;
	char	*rtrn;

	if (cmd[0] == '/')
		return (rtrn = ft_strdup(cmd));
	else
	{
		while (*cmd_paths)
		{
			tmp = ft_strjoin(*cmd_paths, "/");
			rtrn = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(rtrn, F_OK | X_OK) == 0)
				return (rtrn);
			free(rtrn);
			cmd_paths++;
		}
		return (NULL);
	}
}
