/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:18:54 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 11:50:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_var.c
 * @brief Functions to handle expansion of variables.
 */
#include "mod_expand.h"

/**
 * @brief Expand an environment variable in string.
 *
 * Check if special variable - handle with ft_special_var().
 * Else search for variable name and get the variable value.
 * Increase token.len to include $.
 * Insert the replacement in the string.
 * Update the position to be after the inserted replacement.
 * @param input Pointer to tracker.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_NOEXPAND, ERR_MALLOC.
 */
t_err	ft_expand_var(t_track *input, t_hashtable *symtab)
{
	t_str	token;
	t_str	replace;
	t_err	err;

	if (input->str[input->pos + 1] == '?')
		err = ft_special_var(&token, &replace);
	else
	{
		err = ft_get_var_token(input, &token);
		if (err != SUCCESS)
			return (err);
		err = ft_get_var_replace(&token, symtab, &replace);
	}
	if (err != SUCCESS)
		return (err);
	token.len++;
	err = ft_insert_replace(input, token, replace);
	if (replace.len > 0)
		free (replace.ptr);
	input->pos += replace.len;
	input->last_expand_len = replace.len;
	if (err == SUCCESS)
		input->expanded = true;
	return (err);
}

/**
 * @brief Handle the special variable $?
 *
 * @param token Used for token.len
 * @param replace Where to save replace string.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_special_var(t_str *token, t_str *replace)
{
	token->len = 1;
	replace->ptr = ft_itoa(g_status);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
	return (SUCCESS);
}

/**
 * @brief Get variable name token.
 *
 * Sets token.ptr to position after $ and token.len to 0
 * Calc the token.len:
 * As first char after $ only underscore and alphabetic are allowed.
 * After that underscore and alphanumeric are allowed.
 * In case of token.len 0: if a quote follows after $, $ is removed.
 * Else $ is skipped.
 * @param input Pointer to tracker.
 * @param token Pointer to token struct.
 * @return t_err SUCCESS, ERR_NOEXPAND.
 */
t_err	ft_get_var_token(t_track *input, t_str *token)
{
	token->ptr = input->str + input->pos + 1;
	token->len = 0;
	if (token->ptr[token->len] == '_' || ft_isalpha(token->ptr[token->len]))
	{
		token->len++;
		while (token->ptr[token->len] == '_' || ft_isalnum(token->ptr[token->len]))
			token->len++;
	}
	if (token->len == 0)
	{
		if (!input->quoted && ft_strchr("\"'", input->str[input->pos + 1]))
			ft_eat_char(input);
		else
			input->pos++;
		return (ERR_NOEXPAND);
	}
	return (SUCCESS);
}

/**
 * @brief Get replacement for variable.
 *
 * Look for the variable in environment.
 * If not found empty string is ft_strdup(), else var is ft_strdup().
 * Calc the replace.len
 * @param token Pointer to token struct.
 * @param symtab Environment.
 * @param replace Pointer to struct where to save string.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_get_var_replace(t_str *token, t_hashtable *symtab, t_str *replace)
{
	t_env_var	*env_var;

	env_var = ft_hashtable_lookup(symtab, token->ptr, token->len);
	if (!env_var)
		replace->ptr = ft_strdup("");
	else
		replace->ptr = ft_strdup(env_var->value);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
	return (SUCCESS);
}
