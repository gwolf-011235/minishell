/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:20:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/31 18:40:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "libft.h"
# include "minishell_error.h"

# define PS1_STD "$ "
# define PS2_STD "> "

typedef t_error	(*t_replace_ptr)(char **replacement);

//memory.c
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size);

//replace_token.c
t_error	ft_calc_replace_len(const char *str, const char *token,
			const char *replacement, size_t *expanded_len);
t_error	ft_replace_token(char **str, const char *token,
			const char *replacement);

//ft_string.c
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);

#endif