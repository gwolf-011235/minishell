/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/25 08:17:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

# include "libft.h"
# include "hashtable.h"
# include "minishell_error.h"

# define HASHTABLE_SIZE 256

typedef struct s_checks {
	bool	no_env;
	bool	no_pwd;
}	t_checks;

typedef struct s_data {
	t_hashtable	*env_table;
	t_checks	checks;
	t_error		err;
}	t_data;

extern char	**environ;

//exit_failure.c
void	ft_exit_failure(t_data *data, t_error exit_code);

//init.c
t_error	ft_setup_env(t_data *data);
t_error	ft_import_env(t_data *data);

//pwd.c
t_error	ft_create_pwd_value(char **pwd_value);
t_error	ft_create_pwd_env_str(char **pwd);

#endif