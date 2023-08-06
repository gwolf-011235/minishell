/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handle_input.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:47 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/06 18:17:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_HANDLE_INPUT_H
# define MOD_HANDLE_INPUT_H

/* ====== Includes ====== */

# include "minishell_error.h"
# include "minishell_struct.h"
# include "libft.h"

/* ====== Structs ====== */

/**
 * @brief Enum of different types that can be assigned to tokens
 *
 * @param ARG		Any string that is not connected to redirects, piping or newlines.
 * @param INFILE	Redirect evoking an infile.
 * @param HEREDOC	Redirect evoking a heredoc.
 * @param OUTFILE	Redirect evoking an outfile.
 * @param APPEND	Redirect evoking an outfile in append mode.
 * @param PIPE		Char indicating piping of commands.
 * @param Newline	Char indicating end of a command.
 */
typedef enum e_type
{
	ARG,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
	NEW_LINE,
	AMBIGUOUS
}	t_type;

/**
 * @brief List of token.
 *
 * Double-linked list of nodes that contain individual token strings. Each
 * node is connected to the previous and next node. The first node refers to
 * NUll as prev. The last node refers to NULL as next node.
 * @param content String containing token.
 */
typedef struct s_tkn_list
{
	char				*content;
	t_type				type;
	struct s_tkn_list	*prev;
	struct s_tkn_list	*next;
}	t_tkn_list;


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
	char			**delims;
	int				delim_pos;
	bool			append;
	bool			infile;
	bool			outfile;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

/* ====== Functions ====== */

// syntax
t_err		ft_check_syntax(const char *input);

// lexer
t_err		ft_lex_input(t_tkn_list	**lst_head, char *input);
void		ft_free_lst(t_tkn_list **lst);

// expand
t_err		ft_expand_tkn_lst(t_tkn_list **head, t_data *data);
t_err		ft_expand_expr(char **expr, t_hashtable *symtab);

// parser
t_err		ft_parser(t_tkn_list *lst, t_cmd **cmd);

//handle_input_tkn_list.c
t_tkn_list	*ft_last(t_tkn_list *lst);
t_err		ft_new_node(t_tkn_list	**lst_head, char *content);
void		ft_add_lst(t_tkn_list **lst, t_tkn_list *new);
void		ft_add_lst_mid(t_tkn_list *cur, t_tkn_list *new);
t_err		ft_new_node_mid(t_tkn_list **lst_head, char *content);

//handle_input_tkn_list2.c
void		ft_del_node(t_tkn_list *lst);
void		ft_del_node_mid(t_tkn_list **lst_head);
void		ft_free_lst(t_tkn_list **lst);
t_tkn_list	*ft_list_first(t_tkn_list *list);


#endif