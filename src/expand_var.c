/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:18:54 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 14:08:27 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_var.c
 * @brief Functions to handle expansion of variables.
 */
#include "mod_expand.h"

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
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_get_var_replace(t_str token, t_hashtable *symtab, t_str *replace)
{
	t_env_var	*env_var;

	env_var = ft_hashtable_lookup(symtab, token.ptr, token.len);
	if (!env_var)
		replace->ptr = "";
	else
		replace->ptr = ft_strdup(env_var->value);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
	return (SUCCESS);
}

/**
 * @brief Get variable name token.
 *
 * Sets token.str to position after $ and token.len to 0
 * Calc the token.len:
 * As first char after $ only underscore and alphabetic are allowed.
 * After that underscore and alphanumeric are allowed.
 *
 * @param input String.
 * @param pos Current position.
 * @param token Pointer to struct.
 * @return t_err SUCCESS, ERR_NOEXPAND.
 */
t_err	ft_get_var_token(t_track *input, t_str *token, bool quotes)
{
	token->ptr = input->str + input->pos + 1;
	token->len = 0;
	if (token->ptr[token->len] == '_' || ft_isalnum(token->ptr[token->len]))
	{
		token->len++;
		while (token->ptr[token->len] == '_' || ft_isalnum(token->ptr[token->len]))
			token->len++;
	}
	if (token->len == 0)
	{
		if (!quotes && ft_strchr("\"'", input->str[input->pos + 1]))
			ft_eat_char(input->str, input->pos);
		else
			input->pos++;
		return (ERR_NOEXPAND);
	}
	return (SUCCESS);
}

/**
 * @brief Handle the special variables $? and $0
 *
 * @param c Char representing ? or 0.
 * @param replace Where to save replace string.
 * @param token Used for token.len
 * @param info Struct containing ret_code and shell_name
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_special_var(char c, t_str *replace, t_str *token, t_info *info)
{
	token->len = 1;
	if (c == '0')
		replace->ptr = ft_strdup(info->shell_name);
	else if (c == '?')
		replace->ptr = ft_itoa(info->ret_code);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
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
 * @return t_err SUCCESS, ERR_NOEXPAND, ERR_MALLOC.
 */
t_err	ft_expand_var(t_track *input, t_hashtable *symtab, t_info *info, bool quotes)
{
	t_str	token;
	t_str	replace;
	t_err	err;

	if (input->str[input->pos + 1] == '0' || input->str[input->pos + 1] == '?')
		err = ft_special_var(input->str[input->pos + 1], &replace, &token, info);
	else
	{
		err = ft_get_var_token(input, &token, quotes);
		if (err != SUCCESS)
			return (err);
		err = ft_get_var_replace(token, symtab, &replace);
	}
	if (err != SUCCESS)
		return (err);
	token.len++;
	err = ft_insert_replace(input, token, replace);
	if (replace.len > 0)
		free (replace.ptr);
	input->pos += replace.len;
	return (err);
}
