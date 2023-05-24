/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:58:28 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 13:40:40 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

typedef enum e_error {
	SUCCESS,
	ERR_MALLOC,
	ERR_UNDEFINED,
	ERR_HT_NO_INSERT,
	ERR_HT_NO_DELETE,
	ERR_EMPTY,
	ERR_CWD_FAIL
}	t_error;


#endif