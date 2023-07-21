/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_handle_input.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:47 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/21 17:51:29 by sqiu             ###   ########.fr       */
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
	char			*exe;
	char			**args;
	int				fd_in;
	int				fd_out;
	char			*delim;
	bool			append;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

/* ====== Functions ====== */

// syntax
t_err	ft_check_syntax(const char *input);

// lexer
t_err	ft_lex_input(t_tkn_list	**lst_head, char *input);
void	ft_free_lst(t_tkn_list **lst);

//expand
t_err	ft_expand_tkn_lst(t_tkn_list *list, t_data *data);
t_err	ft_expand_expr(char **expr, t_hashtable *symtab, t_info *info);

#endif