/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:18:54 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 12:15:29 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_error	ft_get_var_replace(t_tok token, t_hashtable *symtab, t_tok *replace)
{
	t_env_var	*env_var;

	env_var = ft_hashtable_lookup(symtab, token.str, token.len);
	if (!env_var)
		replace->str = "";
	else
		replace->str = ft_strdup(env_var->value);
	if (!replace->str)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->str);
	return (SUCCESS);
}

t_error	ft_get_var_token(char *input, size_t pos, t_tok *token)
{
	token->str = input + pos + 1;
	token->len = 0;
	if (token->str[token->len] == '_' || ft_isascii(token->str[token->len]))
		token->len++;
	while (token->str[token->len] == '_' || ft_isalnum(token->str[token->len]))
		token->len++;
	return (SUCCESS);
}

t_error	ft_expand_var(char **input, t_hashtable *symtab, size_t *pos)
{
	t_tok	token;
	t_tok	replace;
	t_error	err;

	//special tokens $? and §0
	err = ft_get_var_token(*input, *pos, &token);
	if (token.len == 0)
		return (SUCCESS);
	err = ft_get_var_replace(token, symtab, &replace);
	if (err != SUCCESS)
		return (err);
	err = ft_insert_replace(*input, *pos, token, replace);
	if (replace.len > 0)
		free (replace.str);
	*pos += replace.len;
	return (SUCCESS);
}
