/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handle_input.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:47 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/12 00:08:33 by gwolf            ###   ########.fr       */
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
 * @param exe Pointer to executable string.
 * @param args Pointer to argument string array.
 * @param fd_in File descriptor of infile.
 * @param fd_out File descriptor of outfile.
 * @param delim Pointer to delimiter string.
 * @param append Boole value to indicate append mode.
 * @param index Index indicating position of command in the pipeline.
 */
typedef struct s_cmd
{
	char			**args;
	int				arg_pos;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
	int				fd_prev_pipe[2];
	char			**delims;
	int				delim_pos;
	char			*heredoc;
	bool			append;
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
t_err	ft_lex_input(t_tkn_list	**lst_head, char *input);

// expand
t_err	ft_expand_tkn_lst(t_tkn_list **head, t_hashtable *env_table);

// parser
t_err	ft_parser(t_tkn_list *lst, t_cmd **cmd);

// executor
t_err	ft_executor(t_cmd *cmd, t_data *data);

#endif