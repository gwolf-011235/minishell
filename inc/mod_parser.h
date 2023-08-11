/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:06:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/31 12:35:18 by sqiu             ###   ########.fr       */
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
t_cmd	*ft_lock_and_load_cmd(t_tkn_list *lst, t_cmd *curr, t_cmd **cmd,
			bool *cmd_complete);
t_err	ft_create_cmd(t_cmd **new, t_tkn_list *lst);
t_err	ft_categorise(t_tkn_list **lst, t_cmd *new, bool *cmd_complete);
void	ft_add_cmd(t_cmd *new, t_cmd **cmd);

// fill cmd struc
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_heredoc(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_outfile(t_tkn_list **lst, t_cmd *new, bool append);
t_err	ft_save_arg(t_tkn_list *lst, t_cmd *new);

// helpers
t_cmd	*ft_last_cmd(t_cmd *cmd);
t_err	ft_count_str(t_tkn_list *lst, int *count_arg, int *count_delim);
t_err	ft_create_str_arr(t_cmd *tmp, int count_arg, int count_delim);
void	ft_init_cmd(t_cmd *tmp);

#endif
