/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:38:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 20:06:46 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_cleanup.c
 * @brief Functions for parser cleanup.
 */

#include "mod_parser.h"

/**
 * @brief	Clean up and error output if parser encounters ERR_MALLOC.
 *
 * @param lst_head		Head of token list.
 * @param cmd_head		Head of cmd list.
 * @return t_err		ERR_PARSER
 */
t_err	ft_err_parser(t_tkn_list **lst_head, t_cmd *cmd_head)
{
	g_status = 1;
	ft_free_lst(lst_head);
	ft_cleanup_cmd_list(cmd_head);
	return (ft_print_error(ERR_PARSER));
}
