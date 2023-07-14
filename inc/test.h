/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:32:12 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 19:45:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"
# include "lexer_check_syntax.h"
# include "expander.h"
# include "env_envp.h"

void	test_hashtable(void);
void	test_replace_token(void);
void	test_prompt(void);
void	test_lexer(void);
void	test_check_syntax(void);
void	test_env_envp(void);
void	test_expand(void);

#endif