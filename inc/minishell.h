/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/07 20:48:28 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * @brief Overarching header
 */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ====== LIBRARIES ====== */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

# include "libft.h"
# include "minishell_error.h"
# include "hashtable.h"
# include "lexer.h"

/* ====== DEFINITIONS ====== */

# define HASHTABLE_SIZE 10
# define MAX_SHLVL 10

# define PS1_STD "$ "
# define PS2_STD "> "
# define UNKNOWN "UNKNOWN"

# define PROMPT_EXPAND_SUPPORTED "hnurw"
# define PROMPT_EXPAND_EMPTY "\\"
# define PROMPT_EXPAND_H "\\h"
# define PROMPT_EXPAND_N "\\n"
# define PROMPT_EXPAND_U "\\u"
# define PROMPT_EXPAND_R "\\r"
# define PROMPT_EXPAND_W "\\w"

typedef t_error		(*t_replace_ptr)(char **replacement, t_hashtable *sym_tab);

/**
 * @brief Enumeration containing all token types.
 * 
 */
typedef enum e_tk
{
	EXECUTABLE,
	OPTION,
	INFILE,
	OUTFILE,
	DELIMITER,
	APPEND
}	t_tk;

typedef struct s_tkn_list
{
	void				*content;
	struct s_tkn_list	*prev;
	struct s_tkn_list	*next;
}	t_tkn_list;

/* ====== STRUCTS ====== */

/**
 * @brief Linked list of simple commands existing of token extracted from input. 
 * 
 * Each node of the list contains information about the respective token. Not
 * all variables necessarily need to be populated.
 * @param exc Pointer to executable string.
 * @param opt Pointer to options string.
 * @param redir Pointer to redirection string.
 * @param delim Pointer to delimiter string.
 * @param index Index indicating position of token in the pipeline.
 */
typedef struct s_cmd
{
	char			*exe;
	char			**opts;
	char			*in;
	char			*out;
	char			*delim;
	bool			append;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

/**
 * @brief Flags which can be set to store some info.
 *
 * In this struct some flags can be stored to be set and then be checked
 * later on.
 * @param no_env Environ was empty.
 * @param no_pwd Environ wasn't empty but didn't contain a PWD variable.
 */
typedef struct s_checks {
	bool	no_env;
	bool	no_pwd;
}	t_checks;

/**
 * @brief Overarching struct to hold all necessarry data.
 *
 * This struct will be passed around to give access to several needed
 * var in different programm stages.
 * @param env_table Pointer to the env hashtable.
 * @param checks Struct with some flags.
 * @param err Can hold an error code if data is available - maybe del.
 */
typedef struct s_data {
	t_hashtable	*env_table;
	t_checks	checks;
	t_error		err;
	t_tkn_list	*lst_head;
	t_cmd		*cmds;
	char		*prompt1;
	char		*prompt2;
}	t_data;

/**
 * @brief Global environ which holds the passed environment.
 *
 * More portable solution than the usage of char *envp.
 */
extern char	**environ;

//exit_failure.c
void	ft_exit_failure(t_data *data, t_error exit_code);

//init.c
t_error	ft_env_setup(t_data *data);
t_error	ft_env_import(t_data *data);
t_error	ft_env_insert_pwd(t_data *data);
t_error	ft_env_insert_shlvl(t_data *data);

//pwd.c
t_error	ft_create_pwd_value(char **pwd_value);
t_error	ft_create_pwd_env_str(char **pwd);

//shlvl.c
t_error	ft_create_shlvl_env_str(char **shlvl);
t_error	ft_increment_shlvl(t_data *data);

//ft_memory.c
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size);

//replace_token.c
t_error	ft_calc_replace_len(const char *str, const char *token,
			const char *replacement, size_t *expanded_len);
t_error	ft_replace_token(char **str, const char *token,
			const char *replacement);

//ft_string.c
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);

//prompt.c
t_error	ft_create_prompt(t_hashtable *sym_tab,
			char **prompt, char *ps, char *std);

//prompt_replace_small.c
t_error	ft_prompt_replace_n(char **replacement, t_hashtable *sym_tab);
t_error	ft_prompt_replace_r(char **replacement, t_hashtable *sym_tab);
t_error	ft_prompt_replace_not_found(char **replacement);
t_error	ft_prompt_replace_empty(char **replacement, t_hashtable *sym_tab);

//prompt_replace_h.c
t_error	ft_prompt_replace_h(char **replacement, t_hashtable *sym_tab);
t_error	ft_prompt_create_hostname(char **replacement, const char *str);

//prompt_replace_u.c
t_error	ft_prompt_replace_u(char **replacement, t_hashtable *sym_tab);

//prompt_replace_w.c
t_error	ft_prompt_replace_w(char **replacement, t_hashtable *sym_tab);


#endif