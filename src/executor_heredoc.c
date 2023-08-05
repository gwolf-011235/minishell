/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 11:05:42 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/05 16:31:11 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_heredoc.c
 * @brief Functions to handle heredoc feature.
 */

#include "mod_executor.h"

/**
 * @brief Drive creation of multiple heredocs.
 * 
 * @param cmd 		Current cmd being processed.
 * @return t_err 	ERR_MALLOC, ERR_CLOSE, ERR_BAD_FD, SUCCESS
 */
t_err	ft_handle_heredoc(t_cmd *cmd)
{
	int		i;
	t_err	err;

	i = -1;
	while (++i <= cmd->delim_pos)
	{
		err = ft_create_heredoc(cmd, cmd->delims[i], i);
		if (err != SUCCESS)
			return (err);
	}
	return (SUCCESS);
}

/**
 * @brief Creates a heredoc file.
 * 
 * Stdin (fd = 0) input is written to file until the delimiter
 * is given. Subsequent behaviour handled by ft_heredoc_fate(). 
 * @param cmd 			Current cmd being processed.
 * @param delim			Delimiter string.
 * @param curr_delim 	Current delimiter index.
 * @param t_err			ERR_MALLOC, ERR_CLOSE, ERR_BAD_FD, SUCCESS
 */
t_err	ft_create_heredoc(t_cmd *cmd, char *delim, int curr_delim)
{
	int		fd;
	char	*buf;
	char	*name;
	size_t	len;
	t_err	err;

	err = ft_initiate_heredoc(cmd->index, name, &fd);
	if (err != SUCCESS)
		return (err);
	len = ft_strlen(delim);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		buf = get_next_line(0);
		if (!buf)
			return (ft_unlink_heredoc(name, ERR_MALLOC));
		if ((ft_strncmp(delim, buf, len) == 0) && *(buf + len) == '\n')
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	err = ft_heredoc_fate(cmd, name, fd, curr_delim);
	return (err);
}

/**
 * @brief Define the name of the heredoc file to be created.
 * 
 * Naming follows a base standard enhanced with the index.
 * @param cmd 		Current cmd being processed.
 * @param name 		Name to be defined.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_name_heredoc(int index, char *name)
{
	char	*name;
	char	*index_str;

	index_str = ft_itoa(index);
	name = ft_strjoin(".tmp_heredoc_v", index_str);
	if (!name)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Set heredoc name and open it.
 * 
 * @param index 	Index of current cmd.
 * @param name 		Name of heredoc to be created.
 * @param fd 		File descriptor for heredoc.
 * @return t_err 	ERR_MALLOC, ERR_BAD_FD, SUCCESS
 */
t_err	ft_initiate_heredoc(int index, char *name, int *fd)
{
	t_err	err;

	err = ft_name_heredoc(index, name);
	if (err == ERR_MALLOC)
		return (err);
	*fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
		return (ERR_BAD_FD);
	return (SUCCESS);
}

/**
 * @brief Determines usage of heredoc.
 * 
 * Heredoc set to fd_in if no infile followed the heredocs (fd_in = -1) and
 * it is the last heredoc among several. Else it is unlinked and its name is
 * freed.
 * @param cmd 			Current cmd being processed.
 * @param name 			Malloced name of heredoc.
 * @param fd 			File descriptor of open heredoc.
 * @param curr_delim 	Current delimiter index.
 * @return t_err 		ERR_CLOSE, ERR_BAD_FD, SUCCESS
 */
t_err	ft_heredoc_fate(t_cmd *cmd, char *name, int fd, int curr_delim)
{
	t_err	err;

	err = ft_close(fd);
	if (err != SUCCESS)
		return (err);
	if (cmd->fd_in == -1 && curr_delim == cmd->delim_pos)
	{
		cmd->fd_in = open(name, O_RDONLY);
		if (cmd->fd_in < 0)
			return (ft_unlink_heredoc(name, ERR_BAD_FD));
		cmd->heredoc = name;
	}
	else
		ft_unlink_heredoc(name, SUCCESS);
	return (SUCCESS);
}
