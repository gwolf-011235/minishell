/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:57:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 18:33:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"

//memory
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size);

//string
char	*ft_strcat(char *dst, const char *src);
char	*ft_strncat(char *dst, const char *src, size_t n);
bool	ft_isspace(char c);
bool	ft_isempty_str(const char *s);
void	ft_swap(char **str1, char **str2);

#endif
