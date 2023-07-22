/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/22 20:49:54 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.c
 * @brief 
 */

#include "mod_parser.h"

/**
 * @brief 			Driver function to parse token list.
 * 
 * Creates cmd structures and fills them with the token list.
 * @param lst 		Pointer to list of tokens.
 * @param cmd 		Pointer pointer to first node of cmd list.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_parser(t_tkn_list *lst, t_cmd **cmd)
{
	t_err	err;
	t_cmd	*new;
	bool	exe_found;
	bool	cmd_complete;

	exe_found = 0;
	cmd_complete = 0;
	new = NULL;
	err = ft_init_cmd(new);
	if (err != SUCCESS)
		return (err);
	while (lst)
	{
		err = ft_categorise(lst, new, &exe_found, &cmd_complete);
		if (err != SUCCESS)
			return (err);
		if (cmd_complete)
			new = ft_new_cmd(new, cmd, &exe_found, &cmd_complete);
		if (!new)
			return (ERR_MALLOC);
		lst = lst->next;
	}
	return (SUCCESS);
}

/**
 * @brief Adds current cmd to cmd_list and creates a new cmd struct.
 * 
 * @param curr 			Current cmd struct.
 * @param cmd 			List of cmd structs.
 * @param exe_found 	Bool to indicate if executable has been found.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_cmd* 
 */
t_cmd	*ft_new_cmd(t_cmd *curr, t_cmd **cmd, bool *exe_found,
	bool *cmd_complete)
{
	t_cmd	*new;
	t_err	err;

	new = NULL;
	curr->args = ft_split(curr->arg_buf, ' ');
	ft_add_cmd(curr, cmd);
	err = ft_init_cmd(new);
	if (err != SUCCESS)
		return (NULL);
	*exe_found = 0;
	*cmd_complete = 0;
	return (new);
}

/**
 * @brief Initiates the cmd struct.
 * 
 * @param new Newly created cmd struct.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_init_cmd(t_cmd *new)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (ERR_MALLOC);
	new->append = -1;
	new->arg_buf = NULL;
	new->args = NULL;
	new->delim = NULL;
	new->exe = NULL;
	new->fd_in = -1;
	new->fd_out = -1;
	new->index = -1;
	new->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Sorts token and calls appropriate functions
 * 			to save token into the cmd structure.
 * 
 * @param lst 			Pointer to current token in the list.
 * @param new 			Pointer to cmd structure.
 * @param exe_found 	Bool to indicate if executable has been found.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_err 		SUCCESS
 */
t_err	ft_categorise(t_tkn_list *lst, t_cmd *new, bool *exe_found,
	bool *cmd_complete)
{
	if (lst->content == '<')
		return (ft_save_infile(lst, new));
	else if (ft_strncmp(lst->content, "<<", ft_strlen(lst->content)) == 0)
		return (ft_save_heredoc(lst, new));
	else if (lst->content == '>')
		return (ft_save_outfile(lst, new, 0));
	else if (ft_strncmp(lst->content, ">>", ft_strlen(lst->content)) == 0)
		return (ft_save_outfile(lst, new, 1));
	else if (lst->content == '|')
		*cmd_complete = 1;
	else if (lst->content == '\n')
		return (SUCCESS);
	else if (exe_found)
		return (ft_save_arg(lst, new));
	else
		return (ft_save_exe(lst, new, exe_found));
	return (SUCCESS);
}

/**
 * @brief Add a new cmd structure to the end of cmd-list.
 * 
 * @param new New cmd structure.
 * @param cmd List of cmds.
 */
void	ft_add_cmd(t_cmd *new, t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = ft_last_cmd(*cmd);
	if (tmp)
		tmp->next = new;
	else
		*cmd = new;
}
