/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:06:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/27 10:53:38 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_PARSER_H
# define MOD_PARSER_H

/* ====== Includes ====== */

# include <fcntl.h>					/* required for opening files */
# include "mod_handle_input.h"

/* ====== Structs ====== */

/* ====== Functions ====== */

// cmd list creation
t_cmd	*ft_lock_and_load_cmd(t_tkn_list *lst, t_cmd **cmd,
			bool *cmd_complete);
t_err	ft_create_cmd(t_cmd **new, t_tkn_list *lst, t_cmd **cmd_head);
t_err	ft_categorise(t_tkn_list **lst, t_cmd *new, bool *cmd_complete);
void	ft_add_cmd(t_cmd *new, t_cmd **cmd);

// fill cmd struc
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_heredoc(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_outfile(t_tkn_list **lst, t_cmd *new, bool append);
t_err	ft_save_arg(t_tkn_list *lst, t_cmd *new);
t_err	ft_handle_ambiguous(t_tkn_list **lst, t_cmd *new);

// helpers
t_cmd	*ft_last_cmd(t_cmd *cmd);
void	ft_count_str(t_tkn_list *lst, int *count_arg, int *count_delim,
			int *count_out);
t_err	ft_create_str_arr(t_cmd *tmp, int count_arg, int count_delim,
			int count_out);
void	ft_init_cmd(t_cmd *tmp);
t_err	ft_malloc_arr(char ***str, bool **b_arr, int count);

// cleanup
t_err	ft_err_parser(t_tkn_list **lst_head, t_cmd *cmd_head);

//mod executor
void	ft_cleanup_cmd_list(t_cmd *cmd, char **paths);

#endif
