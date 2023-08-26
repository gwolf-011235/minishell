/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/25 20:09:06 by gwolf            ###   ########.fr       */
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
 * @param cmd_head 	Pointer pointer to first node of cmd list.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_parser(t_tkn_list **lst_head, t_cmd **cmd_head)
{
	t_cmd		*new;
	t_tkn_list	*lst;
	bool		cmd_complete;

	cmd_complete = false;
	new = NULL;
	lst = *lst_head;
	if (ft_create_cmd(&new, lst, cmd_head) == ERR_MALLOC)
		return (ft_err_parser(lst_head, *cmd_head));
	while (lst)
	{
		if (ft_categorise(&lst, new, &cmd_complete) == ERR_MALLOC)
			return (ft_err_parser(lst_head, *cmd_head));
		if (cmd_complete)
			new = ft_lock_and_load_cmd(lst, cmd_head, &cmd_complete);
		if (!new)
			return (ft_err_parser(lst_head, *cmd_head));
		lst = lst->next;
	}
	ft_free_lst(lst_head);
	return (SUCCESS);
}

/**
 * @brief Adds current cmd to cmd_list and creates a new cmd struct.
 *
 * @param lst			List of tokens at end position of previous cmd.
 * @param curr 			Current cmd struct.
 * @param cmd_head 		List of cmd structs.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_cmd*
 */
t_cmd	*ft_lock_and_load_cmd(t_tkn_list *lst, t_cmd **cmd_head,
		bool *cmd_complete)
{
	t_cmd	*new;

	new = NULL;
	lst = lst->next;
	if (ft_create_cmd(&new, lst, cmd_head) == ERR_MALLOC)
		return (NULL);
	*cmd_complete = false;
	return (new);
}

/**
 * @brief Initiates the cmd struct.
 *
 * @param new 		Newly created cmd struct.
 * @param lst		List of tokens at current position.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_create_cmd(t_cmd **new, t_tkn_list *lst, t_cmd **cmd_head)
{
	t_cmd	*tmp;
	int		count_arg;
	int		count_delim;
	int		count_out;

	count_arg = 0;
	count_delim = 0;
	count_out = 0;
	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (ERR_MALLOC);
	ft_init_cmd(tmp);
	ft_count_str(lst, &count_arg, &count_delim, &count_out);
	if (ft_create_str_arr(tmp, count_arg, count_delim, count_out) == ERR_MALLOC)
		return (ERR_MALLOC);
	*new = tmp;
	ft_add_cmd(*new, cmd_head);
	return (SUCCESS);
}

/**
 * @brief Sorts token and calls appropriate functions
 * 			to save token into the cmd structure.
 *
 * @param lst 			Pointer to current token in the list.
 * @param new 			Pointer to cmd structure.
 * @param cmd_complete 	Bool to indicate if cmd ist complete.
 * @return t_err 		SUCCESS, ERR_MALLOC
 */
t_err	ft_categorise(t_tkn_list **lst, t_cmd *new, bool *cmd_complete)
{
	t_tkn_list	*tmp;
	t_err		err;

	err = SUCCESS;
	tmp = *lst;
	if (tmp->type == HEREDOC || tmp->type == QUOTEDOC)
		err = ft_save_heredoc(&tmp, new);
	else if (tmp->type == INFILE)
		err = ft_save_infile(&tmp, new);
	else if (tmp->type == OUTFILE)
		err = ft_save_outfile(&tmp, new, false);
	else if (tmp->type == APPEND)
		err = ft_save_outfile(&tmp, new, true);
	else if (tmp->type == PIPE)
		*cmd_complete = true;
	else if (tmp->type == NEWL)
		return (SUCCESS);
	else if (tmp->type == ARG)
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
