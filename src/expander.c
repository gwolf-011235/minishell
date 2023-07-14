/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:07:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 18:22:46 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_error	ft_insert_replace(char **input, size_t pos, t_tok token, t_tok replace)
{
	size_t	new_len;
	char	*new_str;
	char	*old_str;

	new_len = ft_strlen(*input) - token.len + replace.len;
	new_str = malloc(new_len);
	if (!new_str)
		return (ERR_MALLOC);
	*new_str = '\0';
	old_str = *input;
	ft_strncat(new_str, old_str, pos);
	ft_strcat(new_str, replace.str);
	pos += token.len;
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

t_error	ft_handle_single_quote(char *word, size_t *pos)
{
	ft_eat_char(word, *pos);
	while (word[*pos] != '\'')
		(*pos)++;
	ft_eat_char(word, *pos);
	return (SUCCESS);
}

t_error	ft_handle_double_quote(char *word, size_t pos, bool *in_double_quotes)
{
	ft_eat_char(word, pos);
	*in_double_quotes = !(*in_double_quotes);
	return (SUCCESS);
}

t_error	ft_expand_expr(char **word, t_hashtable *symtab, t_info *info)
{
	size_t	i;
	bool	in_double_quotes;
	t_error	err;

	i = 0;
	in_double_quotes = false;
	err = SUCCESS;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' && !in_double_quotes)
			ft_handle_single_quote(*word, &i);
		else if ((*word)[i] == '"')
			ft_handle_double_quote(*word, i, &in_double_quotes);
		else if ((*word)[i] == '~' && !in_double_quotes)
			err = ft_expand_tilde(word, symtab, &i);
		else if ((*word)[i] == '$')
			err = ft_expand_var(word, symtab, &i, info);
		else
			i++;
		if (err != SUCCESS)
			return (err);
	}
	return (SUCCESS);
}
