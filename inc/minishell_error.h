/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:58:28 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 12:44:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * @brief Header to store error codes
 */
#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

/**
 * @brief Enum, which contains all error codes.
 *
 * To standardize errors, all codes are stored in this enum. It can be used
 * as return type for functions to have uniform error codes.
 *
 */
typedef enum e_error {
	SUCCESS, ///< All went well.
	ERR_MALLOC, ///< Malloc failed.
	ERR_UNDEFINED, ///< Something happened which shouldn't.
	ERR_HT_NO_INSERT, ///< ft_hashtable_insert() could not insert.
	ERR_HT_NO_DELETE, ///< ft_hashtable_delete() could not delete.
	ERR_EMPTY, ///< One or more passed params are empty.
	ERR_CWD_FAIL ///< function getcwd failed.
}	t_error;


#endif