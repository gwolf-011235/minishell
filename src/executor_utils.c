/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:03:04 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/10 18:47:50 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils.c
 * @brief Helper functions for executor.
 */

#include "mod_executor.h"

/**
 * @brief Check given args executable.
 * 
 * Iterate through cmd_paths. If one or more paths are empty (""),
 * boolean "empty_path" is set to true.
 * If args executable contains an absolute path (starts with /),
 * a relative path (starts with ./ or ../), no paths are given or empty_path
 * is true, its validity is checked in the current directory.
 * If not successfully, ERR_UNKNOWN_CMD is returned. In case of empty_path,
 * additionally the right path is searched for.
 * 
 * If none of the above is applicable solely an attempt to find and assign
 * the right path is started. If not successfully, ERR_UNKNOWN_CMD is returned.  
 * @param args 			String array containing executable in first position.
 * @param cmd_paths 	String array of paths.
 * @return t_err 		ERR_UNKNOWN_CMD, ERR_MALLOC, SUCCESS
 */
t_err	ft_check_cmd_access(char **args, char **cmd_paths)
{
	t_err	err;
	char	**tmp;
	bool	empty_path;

	err = ERR_UNKNOWN_CMD;
	tmp = cmd_paths;
	empty_path = false;
	while (*tmp)
	{
		if (**tmp == '\0')
			empty_path = true;
		tmp++;
	}
	if ((*args)[0] == '/' || !ft_strncmp(*args, "./", 2)
		|| !ft_strncmp(*args, "../", 3) || !cmd_paths || empty_path)
	{
		if (access(*args, F_OK | X_OK) == 0)
			return (SUCCESS);
		if (empty_path)
			err = ft_prefix_path(args, cmd_paths);
	}
	else
		err = ft_prefix_path(args, cmd_paths);
	return (err);
}

/**
 * @brief Prefix the correct path before the executable.
 * 
 * Rotate through all paths and checks whether the combination
 * with the executable is correct. If unsucessful, ERR_UNKNOWN_CMD is
 * returned.
 * @param args 			String array containing executable in first position.
 * @param cmd_paths 	String array of paths.
 * @return t_err 		ERR_UNKNOWN_CMD, ERR_MALLOC, SUCCESS
 */
t_err	ft_prefix_path(char **args, char **cmd_paths)
{
	char	*tmp;
	char	*rtrn;

	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		rtrn = ft_strjoin(tmp, *args);
		free(tmp);
		if (!rtrn)
			return (ERR_MALLOC);
		if (access(rtrn, F_OK | X_OK) == 0)
		{
			free(*args);
			*args = rtrn;
			return (SUCCESS);
		}
		free(rtrn);
		cmd_paths++;
	}
	return (ERR_UNKNOWN_CMD);
}

/**
 * @brief Get the path object from envp str array.
 * 
 * Loop through the envp string array.
 * If envp str is PATH, then 0 || 0 -> exit while loop.
 * If envp str is PATH2, then 0 || 1 -> stay in while loop.
 * If no PATH is found (*envp = NULL), return ERR_NOPATH.
 * If PATH is empty, a '\0' is found and saved into *paths. This will
 * be treated as ERR_NOPATH as well.
 * @param envp 		String array containing all environment strings.
 * @param paths		Pointer to string array containing all path strings.
 * @return t_err	ERR_NOPATH, ERR_MALLOC, SUCCESS
 */
t_err	ft_get_path(char **envp, char ***paths)
{
	char	*path_str;

	while (*envp && (ft_strncmp(*envp, "PATH", 4) || (*(*envp + 4) != '=')))
		envp++;
	if (!*envp)
		return (ERR_NOPATH);
	path_str = *envp + 5;
	*paths = ft_split(path_str, ':');
	if (!*paths)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Replace the standard file descriptors
 * 
 * 	fd 0 (for system stdinput) with input_fd
 * 	fd 1 (for system stdoutput) with output_fd
 *
 * allowing data to be read and written to different files.
 * The input and output fds are closed after transfering their
 * file description to stdin and stdout respectively.
 * @param input_fd 		File descriptor to act as read end.
 * @param output_fd 	File descriptor to act as write end.
 * @return t_err		ERR_DUPL, SUCCESS
 */
t_err	ft_replace_fd(int input_fd, int output_fd)
{
	if (dup2(input_fd, 0) < 0)
		return (ERR_DUPL);
	if (dup2(output_fd, 1) < 0)
		return (ERR_DUPL);
	return (SUCCESS);
}

/**
 * @brief Wait for child processes
 * 
 * @param cmd 		List of cmds.
 * @return t_err 	ERR_WAIT, SUCCESS
 */
t_err	ft_wait_for_babies(t_cmd *cmd)
{
	while (cmd)
	{
		if (waitpid(cmd->pid, NULL, 0) < 0) // retrieve exit status
			return (ERR_WAIT);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
