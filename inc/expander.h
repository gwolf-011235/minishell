/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:08:04 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/13 22:19:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell_error.h"
# include "hashtable.h"
# include "ft_string.h"

typedef struct s_expand_checks {
	bool	in_double_quotes;
	bool	at_start;
	bool	in_assign;
}	t_expand_checks;

t_error	ft_expand_words(char **word, t_hashtable *symtab);
t_error	ft_insert_replace(char **input, size_t pos, char *token, char *replace);

t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos);

#endif