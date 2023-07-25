/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:32:12 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 15:39:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"
# include "mod_env.h"
# include "mod_expand.h"
# include "mod_handle_input.h"
# include "mod_lexer.h"
# include "mod_prompt.h"
# include "mod_syntax.h"
# include "mod_builtin.h"

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define BLACK "\033[30m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define BLUE "\033[34m"

void	test_setup_data(void);
void	test_teardown_data(void);
void	test_setup_argv(size_t size);
void	test_teardown_argv(void);
void	test_free_argv_elem(size_t index);

void	test_hashtable(void);
void	test_replace_token(void);
void	test_prompt(void);
void	test_lexer(void);
void	test_check_syntax(void);
void	test_env_envp(void);
void	test_expand(void);
void	test_expand_list(void);
void	test_builtin_echo(void);
void	test_builtin_cd(void);
void	test_builtin_pwd(void);
void	test_builtin_export(void);
void	test_builtin_unset(void);
void	test_builtin_env(void);
void	test_builtin_exit(void);

#endif