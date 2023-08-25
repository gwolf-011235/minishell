/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:58:28 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/25 20:56:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file  minishell_error.h
 * @brief Header to store error codes
 */
#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# include <errno.h>

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

# include "libft.h"

/* ====== Globals ====== */

extern __sig_atomic_t	g_status;

/* ====== Typedefs ====== */

/**
 * @brief Enum, which contains all error codes.
 *
 * To standardize errors, all codes are stored in this enum. It can be used
 * as return type for functions to have uniform error codes.
 *
 */
typedef enum e_error {
	ERR_EOF = -1,
	SUCCESS, ///< All went well.
	ERR_MALLOC, ///< Malloc failed.
	ERR_UNDEFINED, ///< Something happened which shouldn't.
	ERR_HT_NO_INSERT, ///< ft_hashtable_insert() could not insert.
	ERR_HT_NO_DELETE, ///< ft_hashtable_delete() could not delete.
	ERR_HT_NO_SWAP, ///< ft_hashtable_swap() didn't find element.
	ERR_EMPTY, ///< One or more passed params are empty.
	ERR_CWD_BUF, ///< Buffer size for cwd was too small.
	ERR_CWD_FAIL, ///< function getcwd failed.
	ERR_NO_SHLVL, ///< ft_increment_shlvl didn't find SHLVL.
	ERR_OUT_OF_BOUNDS, ///< A parameter has exceeded the allowed range.
	ERR_WRONG_TOKEN, ///< A prompt substitution was not recognized.
	ERR_SYNTAX = 2, ///< Syntax error with quotes, pipes or redirect.
	ERR_NOT_FOUND, ///< If a search failed.
	ERR_NO_HOME, /// HOME not set.
	ERR_NO_OLDPWD, /// OLDPWD not set.
	ERR_NOEXPAND, ///< Expansion of a token failed.
	ERR_CLOSE, ///< Closing fd failed.
	ERR_ARGCOUNT, ///< Too many arguments where counted.
	ERR_CHDIR_FAIL, ///< function chdir() failed.
	ERR_INVALID_NAME, ///< Not a valid env name.
	ERR_NONUM, ///< The string doesn't represent a number.
	ERR_EXIT, ///< ft_exit() failed because of too many args.
	ERR_PIPE, ///< Piping failed.
	ERR_UNKNOWN_CMD, ///< Command not found.
	ERR_NOPATH, ///< No path found.
	ERR_FORK, ///< Failure to fork.
	ERR_DUPL, ///< Error while duplicating file descriptor.
	ERR_EXECVE, ///< Execve encountered an error.
	ERR_WAIT, ///< Error while waiting for exit status of child process.
	ERR_NOSPLIT, ///< ft_field_split() didnt split.
	ERR_OPEN, ///< open() failed.
	ERR_SIGNAL, ///< Setup of signal handler failed.
	ERR_NO_INPUT, ///< Input is empty.
	ERR_ABORT, ///< Abort pipeline.
	ERR_HEREDOC_EOF, ///< Heredoc stopped by Ctrl+D
	ERR_WRITE, ///< Syscall write failed.
	ERR_DIR, ///< Cmd is a directory.
	ERR_NO_DIR, ///< Directory or file not found
	ERR_STAT, ///< stat() failed.
	ERR_LEXER, ///< Error while lexing.
	ERR_EXPANDER, ///< Error while expanding.
	ERR_PARSER, ///< Error while parsing.
	ERR_AMBIGUOUS, ///< Ambiguous redirect after expand.
	ERR_HEREDOC_OPEN ///< Error while opening heredoc.
}	t_err;

/* ====== Functions ====== */

//error.c
t_err	ft_err_write(int fd, char *str, char *msg);
t_err	ft_err_chdir(char *path, char *msg);
t_err	ft_err_stat(const char *pathname, struct stat *statbuf, char *msg);
t_err	ft_err_malloc(void **ptr, size_t size, char *msg);
t_err	ft_err_getcwd(char *buf, size_t size, char *msg);

//error2.c
t_err	ft_err_strdup(const char *src, char **dst, char *msg);
t_err	ft_err_itoa(int n, char **dst, char *msg);
t_err	ft_err_strjoin(const char *s1, const char *s2, char **dst, char *msg);

//error3.c
t_err	ft_err_open(const char *path, int flag, int *fd, char *msg);
t_err	ft_err_close(int fd, char *msg);

//error_msg.c
t_err	ft_print_warning(t_err err, char *trigger);
t_err	ft_print_warning2(t_err err, char *trigger);
t_err	ft_print_warning3(t_err err, char *trigger);
t_err	ft_print_error(t_err err);


#endif
