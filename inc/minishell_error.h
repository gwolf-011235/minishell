/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:58:28 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 16:59:52 by sqiu             ###   ########.fr       */
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
 * @param 	SUCCESS, ///< All went well.
 * @param	ERR_MALLOC, ///< Malloc failed.
 * @param	ERR_UNDEFINED, ///< Something happened which shouldn't.
 * @param	ERR_HT_NO_INSERT, ///< ft_hashtable_insert() could not insert.
 * @param	ERR_HT_NO_DELETE, ///< ft_hashtable_delete() could not delete.
 * @param	ERR_HT_NO_SWAP, ///< ft_hashtable_swap() didn't find element.
 * @param	ERR_EMPTY, ///< One or more passed params are empty.
 * @param 	ERR_CWD_BUF, ///< Buffer size for cwd was too small.
 * @param	ERR_CWD_FAIL, ///< function getcwd failed.
 * @param	ERR_NO_SHLVL, ///< ft_increment_shlvl didn't find SHLVL.
 * @param	ERR_OUT_OF_BOUNDS, ///< A parameter has exceeded the allowed range.
 * @param	ERR_WRONG_TOKEN, ///< A prompt substitution was not recognized.
 * @param	ERR_SYNTAX = 2, ///< Syntax error with quotes, pipes or redirect.
 * @param	ERR_NOT_FOUND, ///< If a search failed.
 * @param	ERR_NO_HOME, /// HOME not set.
 * @param	ERR_NO_OLDPWD, /// OLDPWD not set.
 * @param	ERR_NOEXPAND, ///< Expansion of a token failed.
 * @param	ERR_CLOSE, ///< Closing fd failed.
 * @param	ERR_ARGCOUNT, ///< Too many arguments where counted.
 * @param	ERR_CHDIR_FAIL, ///< function chdir() failed.
 * @param	ERR_INVALID_NAME, ///< Not a valid env name.
 * @param	ERR_NONUM, ///< The string doesn't represent a number.
 * @param	ERR_EXIT, ///< ft_exit() failed because of too many args.
 * @param	ERR_PIPE, ///< Piping failed.
 * @param	ERR_UNKNOWN_CMD, ///< Command not found.
 * @param	ERR_NOPATH, ///< No path found.
 * @param	ERR_FORK, ///< Failure to fork.
 * @param	ERR_DUPL, ///< Error while duplicating file descriptor.
 * @param	ERR_EXECVE, ///< Execve encountered an error.
 * @param	ERR_WAIT, ///< Error while waiting for exit status of child process.
 * @param	ERR_NOSPLIT, ///< ft_field_split() didnt split.
 * @param	ERR_OPEN, ///< open() failed.
 * @param	ERR_SIGNAL, ///< Setup of signal handler failed.
 * @param	ERR_NO_INPUT, ///< Input is empty.
 * @param	ERR_ABORT, ///< Abort pipeline.
 * @param	ERR_HEREDOC_EOF, ///< Heredoc stopped by Ctrl+D
 * @param	ERR_WRITE, ///< Syscall write failed.
 * @param	ERR_DIR, ///< Cmd is a directory.
 * @param	ERR_NO_DIR, ///< Directory or file not found
 * @param	ERR_STAT, ///< stat() failed.
 * @param	ERR_LEXER, ///< Error while lexing.
 * @param	ERR_EXPANDER, ///< Error while expanding.
 * @param	ERR_PARSER, ///< Error while parsing.
 * @param	ERR_AMBIGUOUS, ///< Ambiguous redirect after expand.
 * @param	ERR_HEREDOC_OPEN, ///< Error while opening heredoc.
 * @param	ERR_EXECUTOR, ///< Error while executing.
 * @param	ERR_IS_CHILD,///< Process is a child.
 * @param	ERR_PERM_DENIED, ///< No executable rights.
 */

typedef enum e_error {
	ERR_EOF = -1,
	SUCCESS, 
	ERR_MALLOC,
	ERR_UNDEFINED, 
	ERR_HT_NO_INSERT, 
	ERR_HT_NO_DELETE,
	ERR_HT_NO_SWAP, 
	ERR_EMPTY, 
	ERR_CWD_BUF, 
	ERR_CWD_FAIL,
	ERR_NO_SHLVL, 
	ERR_OUT_OF_BOUNDS, 
	ERR_WRONG_TOKEN,
	ERR_SYNTAX = 2,
	ERR_NOT_FOUND,
	ERR_NO_HOME,
	ERR_NO_OLDPWD,
	ERR_NOEXPAND,
	ERR_CLOSE,
	ERR_ARGCOUNT,
	ERR_CHDIR_FAIL,
	ERR_INVALID_NAME,
	ERR_NONUM, 
	ERR_EXIT, 
	ERR_PIPE, 
	ERR_UNKNOWN_CMD,
	ERR_NOPATH,
	ERR_FORK,
	ERR_DUPL, 
	ERR_EXECVE, 
	ERR_WAIT, 
	ERR_NOSPLIT, 
	ERR_OPEN,
	ERR_SIGNAL,
	ERR_NO_INPUT,
	ERR_ABORT, 
	ERR_HEREDOC_EOF,
	ERR_WRITE, 
	ERR_DIR,
	ERR_NO_DIR, 
	ERR_STAT,
	ERR_LEXER,
	ERR_EXPANDER,
	ERR_PARSER,
	ERR_AMBIGUOUS,
	ERR_HEREDOC_OPEN, 
	ERR_EXECUTOR,
	ERR_IS_CHILD,
	ERR_PERM_DENIED,
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
t_err	ft_err_pipe(int pipes[2], char *msg);
void	ft_err_execve(char *exec, char **args, char **envp);

//error_msg.c
t_err	ft_print_warning(t_err err, char *trigger);
t_err	ft_print_warning2(t_err err, char *trigger);
t_err	ft_print_warning3(t_err err, char *trigger);
t_err	ft_print_error(t_err err);

#endif
