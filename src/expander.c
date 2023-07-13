/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/13 22:20:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_error	ft_calc_new_len(char *input, char *token, char *replace, size_t *new_len)
{
	size_t	input_len;
	size_t	token_len;
	size_t	replace_len;

	input_len = ft_strlen(input);
	token_len = ft_strlen(token);
	replace_len = ft_strlen(replace);
	*new_len = input_len - token_len + replace_len + 1;
	return (SUCCESS);
}

t_error	ft_insert_replace(char **input, size_t pos, char *token, char *replace)
{
	size_t	new_len;
	char	*new_str;
	char	*old_str;

	new_len = 0;
	ft_calc_new_len(*input, token, replace, &new_len);
	new_str = malloc(new_len);
	if (!new_str)
		return (ERR_MALLOC);
	*new_str = '\0';
	old_str = *input;
	ft_strncat(new_str, old_str, pos);
	ft_strcat(new_str, replace);
	pos += ft_strlen(token);
	ft_strcat(new_str, (old_str + pos));
	free(old_str);
	*input = new_str;
	return (SUCCESS);
}

t_error	ft_eat_char(char *input, size_t pos)
{
	char	*str1;
	char	*str2;

	str1 = input + pos;
	str2 = str1 + 1;
	while (*str1)
	{
		*str1++ = *str2++;
	}
	return (SUCCESS);
}
/*
t_error	ft_expand_symbol(char *input, t_hashtable *symtab, char **output)
{
	size_t		strlen;
	t_env_var	*target;

	*input++;
	strlen = ft_strlen(input);
	target = ft_hashtable_lookup(symtab, *input, strlen);
	if (!target)
		return (ERR_NOT_FOUND);
	*output = ft_strdup(target->value);
	if (!*output)
		return (ERR_MALLOC);
	return (SUCCESS);
}
*/

//get string.
//loop through string
//expand if condition is met.

t_error	ft_expand_words(char **word, t_hashtable *symtab)
{
	size_t	i;
	bool	in_double_quotes;

	i = 0;
	in_double_quotes = false;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' && !in_double_quotes)
		{
			ft_eat_char(*word, i);
			while ((*word)[i] != '\'')
				i++;
			ft_eat_char(*word, i);
		}
		else if ((*word)[i] == '"')
		{
			ft_eat_char(*word, i);
			in_double_quotes = !in_double_quotes;
		}
		else if ((*word)[i] == '~' && !in_double_quotes)
			ft_expand_tilde(word, symtab, &i);
		i++;
	}
	return (SUCCESS);
}
