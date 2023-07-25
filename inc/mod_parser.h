/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:06:32 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/26 01:23:11 by sqiu             ###   ########.fr       */
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
t_cmd	*ft_new_cmd(t_cmd *curr, t_cmd **cmd, bool *exe_found,
			bool *cmd_complete);
t_err	ft_init_cmd(t_cmd **new);
t_err	ft_categorise(t_tkn_list **lst, t_cmd *new, bool *exe_found,
			bool *cmd_complete);
void	ft_add_cmd(t_cmd *new, t_cmd **cmd);

// fill cmd struc
t_err	ft_save_infile(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_heredoc(t_tkn_list **lst, t_cmd *new);
t_err	ft_save_outfile(t_tkn_list **lst, t_cmd *new, bool append);
t_err	ft_save_exe(t_tkn_list *lst, t_cmd *new, bool *exe_found);
t_err	ft_save_arg(t_tkn_list *lst, t_cmd *new);

// helpers
t_cmd	*ft_last_cmd(t_cmd *cmd);
t_err	ft_finish_cmd_list(t_cmd *new, t_cmd **cmd);

#endif
