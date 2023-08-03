/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:03:04 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/03 23:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_executor.h"

/* This function prefixes the appropriate path in front of the command,
if that is not already the case. To this aim, it rotates through all
command paths and checks whether the combination with the command is
correct via 'access'. If so, the command including its path is returned.
In case of failure to find a working path to the command NULL is returned. */

char	*ft_prefix_path(char *cmd, char **cmd_paths)
{
	char	*tmp;
	char	*rtrn;

	if (cmd[0] == '/')
		return (cmd);
	else
	{
		while (*cmd_paths)
		{
			tmp = ft_strjoin(*cmd_paths, "/");
			rtrn = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(rtrn, F_OK | X_OK) == 0)
			{
				free(cmd);
				return (rtrn);
			}
			free(rtrn);
			cmd_paths++;
		}
		return (NULL);
	}
}

/**
 * @brief Get the path object
 * 
 * @param envp 
 * @return char* 
 */
char	**ft_get_path(char **envp)
{
	char	*path_str;
	char	**paths;

	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	path_str = *envp + 5;
	paths = ft_split(path_str, ':');
	if (!paths)
		return (NULL);
	return (paths);
}
