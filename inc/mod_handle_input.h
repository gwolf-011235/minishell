/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handle_input.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:47 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/22 18:08:48 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_HANDLE_INPUT_H
# define MOD_HANDLE_INPUT_H

/* ====== Includes ====== */

# include "minishell_error.h"
# include "minishell_struct.h"
# include "libft.h"
# include "tkn_list.h"
# include <fcntl.h>			        /* required for opening files */
# include <sys/wait.h>				/* required for wait calls */
# include "stdbool.h"				/* required for booleans */
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>


/* ====== Structs ====== */

/**
 * @brief Linked list of simple commands existing of token extracted from input.
 *
 * Each node of the list contains information about the respective token. Not
 * all variables necessarily need to be populated.
 * @param args Pointer to argument string array.
 * @param arg_pos Position of arg in arg array.
 * @param fd_in File descriptor of infile.
 * @param fd_out File descriptor of outfile.
 * @param fd_pipe Integer array containing the read/write end of the pipe
 * connecting this cmd to the next one.
 * @param fd_prev_pipe Integer array containing the read/write end of the
 * previous pipe.
 * @param delims Pointer to delimiter string array.
 * @param delim_pos Position of delimiter in delim array.
 * @param heredoc Pointer to Heredoc name string.
 * @param outfiles Pointer to outfile name string array.
 * @param append Boolean value to indicate append mode.
 * @param infile Boolean value to indicate infile(s) have been found.
 * @param outfile Boolean value to indicate outfile(s) have been found.
 * @param index Index indicating position of command in the pipeline.
 * @param cmd_num Total number of cmds in list.
 * @param pid Process identifier for forking the cmd execution.
 * @param next Pointer to next cmd.
 */
typedef struct s_cmd
{
	bool			execute;
	char			**args;
	int				arg_pos;
	char			**delims;
	int				delim_pos;
	bool			*hdoc_quoted;
	char			*heredoc;
	char			**outfiles;
	int				out_pos;
	bool			*append_switches;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
	int				fd_prev_pipe[2];
	bool			infile;
	bool			outfile;
	int				index;
	int				cmd_num;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

/* ====== Functions ====== */

// syntax
t_err	ft_check_syntax(const char *input);

// lexer
t_err	ft_lex_input(t_tkn_list	**lst_head, char *input, t_buf *buf);

// expand
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_hashtable *env_table, t_buf *buf);

// parser
t_err	ft_parser(t_tkn_list *lst, t_cmd **cmd);

// executor
t_err	ft_executor(t_cmd *cmd, t_data *data);
void	ft_cleanup_cmd_list(t_cmd *cmd);

#endif