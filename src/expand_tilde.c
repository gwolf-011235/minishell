/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 12:48:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"expander.h"

t_error	ft_get_tilde_replace(t_tok token, t_hashtable *symtab, t_tok *replace)
{
	char		*target;
	t_env_var	*env_var;

	if (!ft_strcmp(token.str, "~"))
		target = "HOME";
	else if (!ft_strcmp(token.str, "~+"))
		target = "PWD";
	else if (!ft_strcmp(token.str, "~-"))
		target = "OLDPWD";
	env_var = ft_hashtable_lookup(symtab, target, ft_strlen(target));
	if (!env_var)
		return (ERR_NOT_FOUND);
	replace->str = ft_strdup(env_var->value);
	if (!replace->str)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->str);
	return (SUCCESS);
}

t_error	ft_get_tilde_token(char *input, size_t pos, t_tok *token)
{
	token->str = "~";
	pos++;
	if (input[pos] == '+')
	{
		token->str = "~+";
		pos++;
	}
	else if (input[pos] == '-')
	{
		token->str = "~-";
		pos++;
	}
	if (input[pos] != '\\' && input[pos] != '\0')
		token->str = NULL;
	if (token->str)
		token->len = ft_strlen(token->str);
	return (SUCCESS);
}

t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos)
{
	t_tok	token;
	t_tok	replace;
	t_error	err;

	if (*pos != 0 && (*input)[*pos - 1] != '=')
		return (SUCCESS);
	token.str = NULL;
	ft_get_tilde_token(*input, *pos, &token);
	if (!token.str)
		return (SUCCESS);
	replace.str = NULL;
	err = ft_get_tilde_replace(token, symtab, &replace);
	if (err == ERR_NOT_FOUND)
	{
		(*pos)++;
		return (SUCCESS);
	}
	if (err != SUCCESS)
		return (err);
	err = ft_insert_replace(input, *pos, token, replace);
	free(replace.str);
	if (err != SUCCESS)
		return (err);
	*pos += replace.len;
	return (SUCCESS);
}
