/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/28 13:15:31 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.c
 * @brief Contains functions to parse the token list, categorise the tokens and
 * create a cmd list.
 */

#include "mod_parser.h"

/**
 * @brief 			Driver function to parse token list.
 * 
 * Creates cmd structures and fills them with the token list.
 * @param lst 		Pointer to list of tokens.
 * @param cmd_head 		Pointer pointer to first node of cmd list.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_parser(t_tkn_list *lst, t_cmd **cmd_head)
{
	t_err	err;
	t_cmd	*new;
	bool	cmd_complete;

	cmd_complete = 0;
	new = NULL;
	err = ft_create_cmd(&new, lst);
	if (err != SUCCESS)
		return (err);
	while (lst)
	{
		err = ft_categorise(&lst, new, &cmd_complete);
		if (err != SUCCESS)
			return (err);
		if (cmd_complete)
			new = ft_new_cmd(lst, new, cmd_head, &cmd_complete);
		if (!new)
			return (ERR_MALLOC);
		lst = lst->next;
	}
	ft_add_cmd(new, cmd_head);
	return (SUCCESS);
}

/**
 * @brief Adds current cmd to cmd_list and creates a new cmd struct.
 * 
 * @param lst			List of tokens at end position of previous cmd.
 * @param curr 			Current cmd struct.
 * @param cmd_head 		List of cmd structs.
 * @param exe_found 	Bool to indicate if executable has been found.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_cmd* 
 */
t_cmd	*ft_new_cmd(t_tkn_list *lst, t_cmd *curr, t_cmd **cmd_head,
		bool *cmd_complete)
{
	t_cmd	*new;
	t_err	err;

	new = NULL;
	ft_add_cmd(curr, cmd_head);
	lst = lst->next;
	err = ft_create_cmd(&new, lst);
	if (err != SUCCESS)
		return (NULL);
	*cmd_complete = 0;
	return (new);
}

/**
 * @brief Initiates the cmd struct.
 * 
 * @param new Newly created cmd struct.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_create_cmd(t_cmd **new, t_tkn_list *lst)
{
	t_cmd	*tmp;
	t_err	err;
	int		count_arg;
	int		count_delim;

	count_arg = 0;
	count_delim = 0;
	ft_count_str(lst, &count_arg, &count_delim);
	err = ft_create_str_arr(&tmp, count_arg, count_delim);
	if (err != SUCCESS)
		return (err);
	tmp->arg_pos = 0;
	tmp->delim_pos = 0;
	tmp->append = 0;
	tmp->fd_in = -1;
	tmp->fd_out = -1;
	tmp->infile = 0;
	tmp->outfile = 0;
	tmp->index = -1;
	tmp->next = NULL;
	*new = tmp;
	return (SUCCESS);
}

/**
 * @brief Sorts token and calls appropriate functions
 * 			to save token into the cmd structure.
 * 
 * @param lst 			Pointer to current token in the list.
 * @param new 			Pointer to cmd structure.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_err 		SUCCESS
 */
t_err	ft_categorise(t_tkn_list **lst, t_cmd *new, bool *cmd_complete)
{
	t_tkn_list	*tmp;
	t_err		err;

	err = SUCCESS;
	tmp = *lst;
	if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) == 0)
		err = ft_save_infile(&tmp, new);
	else if (ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0)
		err = ft_save_heredoc(&tmp, new);
	else if (ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)) == 0)
		err = ft_save_outfile(&tmp, new, 0);
	else if (ft_strncmp(tmp->content, ">>", ft_strlen(tmp->content)) == 0)
		err = ft_save_outfile(&tmp, new, 1);
	else if (ft_strncmp(tmp->content, "|", ft_strlen(tmp->content)) == 0)
		*cmd_complete = 1;
	else if (ft_strncmp(tmp->content, "\n", ft_strlen(tmp->content)) == 0)
		return (SUCCESS);
	else
		err = ft_save_arg(tmp, new);
	if (err != SUCCESS)
		return (err);
	*lst = tmp;
	return (SUCCESS);
}

/**
 * @brief Add a new cmd structure to the end of cmd-list.
 * 
 * @param new New cmd structure.
 * @param cmd_head List of cmds.
 */
void	ft_add_cmd(t_cmd *new, t_cmd **cmd_head)
{
	t_cmd	*tmp;

	tmp = ft_last_cmd(*cmd_head);
	if (tmp)
		tmp->next = new;
	else
		*cmd_head = new;
}
