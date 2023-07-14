/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:18:54 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/14 19:38:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_var.c
 * @brief Functions to handle expansion of variables.
 */
#include "expander.h"

/**
 * @brief Get replacement for variable.
 *
 * Look for the variable in environment.
 * If not found empty string is assigned, else var is ft_strdup().
 * Calc the replace.len
 *
 * @param token Info about the variable.
 * @param symtab Environment.
 * @param replace Pointer to struct where to save string.
 * @return t_error SUCCESS, ERR_MALLOC.
 */
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

/**
 * @brief Get variable name token.
 *
 * Sets token.str to position after $ and token.len to 0
 * Calc the token.len:
 * As first char after $ only underscore and ascii are allowed.
 * After that underscore and alphanumeric are allowed.
 *
 * @param input String.
 * @param pos Current position.
 * @param token Pointer to struct.
 * @return t_error SUCCESS.
 */
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

/**
 * @brief Handle the special variables $? and $0
 *
 * @param c Char representing ? or 0.
 * @param replace Where to save replace string.
 * @param token Used for token.len
 * @param info Struct containing ret_code and shell_name
 * @return t_error SUCCESS, ERR_MALLOC
 */
t_error	ft_special_var(char c, t_tok *replace, t_tok *token, t_info *info)
{
	token->len = 1;
	if (c == '0')
		replace->str = ft_strdup(info->shell_name);
	else if (c == '?')
		replace->str = ft_itoa(info->ret_code);
	if (!replace->str)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->str);
	return (SUCCESS);
}

/**
 * @brief Expand an environment variable in string.
 *
 * Check if special variable - handle with ft_special_var().
 * Else search for variable name and get the variable value.
 * Increase token.len to include $.
 * Insert the replacement in the string.
 * Update the position to be after the inserted replacement.
 *
 * @param input Input string.
 * @param symtab Environment.
 * @param pos Current position.
 * @param info Struct containing ret_code and shell_name.
 * @return t_error SUCCESS, ERR_MALLOC.
 */
t_error	ft_expand_var(char **input, t_hashtable *symtab, size_t *pos, t_info *info)
{
	t_tok	token;
	t_tok	replace;
	t_error	err;

	if ((*input)[*pos + 1] == '0' || (*input)[*pos + 1] == '?')
		err = ft_special_var((*input)[*pos + 1], &replace, &token, info);
	else
	{
		err = ft_get_var_token(*input, *pos, &token);
		if (token.len == 0)
			return (SUCCESS);
		err = ft_get_var_replace(token, symtab, &replace);
	}
	if (err != SUCCESS)
		return (err);
	token.len++;
	err = ft_insert_replace(input, *pos, token, replace);
	if (replace.len > 0)
		free (replace.str);
	*pos += replace.len;
	return (err);
}
