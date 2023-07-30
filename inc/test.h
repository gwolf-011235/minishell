/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:32:12 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 14:47:07 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"
# include "mod_env.h"
# include "mod_expand.h"
# include "mod_handle_input.h"
# include "mod_prompt.h"
# include "mod_syntax.h"

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define BLACK "\033[30m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define BLUE "\033[34m"

void	test_setup_data(void);
void	test_teardown_data(void);

void	test_hashtable(void);
void	test_replace_token(void);
void	test_prompt(void);
void	test_lexer(void);
void	test_check_syntax(void);
void	test_env_envp(void);
void	test_expand(void);
void	test_expand_list(void);
void	test_parser(void);

#endif