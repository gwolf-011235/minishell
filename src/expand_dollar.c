/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:18:54 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/19 00:17:50 by gwolf            ###   ########.fr       */
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
 * Check if special variable - handle with ft_special_dollar().
 * Else search for variable name and get the variable value.
 * Increase var.len to include $.
 * Insert the replacement in the string.
 * Update the position to be after the inserted replacement.
 * @param input Pointer to tracker.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_NOEXPAND, ERR_MALLOC.
 */
t_err	ft_expand_dollar(t_track *input, t_hashtable *symtab)
{
	t_str	var;
	t_str	replace;
	t_err	err;
	char	next;

	next = input->str[input->pos +1];
	if (next == '?' || next == '$')
		err = ft_special_dollar(&var, &replace, symtab, next);
	else
	{
		err = ft_get_dollar_var(input, &var);
		if (err != SUCCESS)
			return (err);
		err = ft_get_dollar_replace(&var, symtab, &replace);
	}
	if (err != SUCCESS)
		return (err);
	var.len++;
	err = ft_insert_replace(input, var, replace);
	if (replace.len > 0)
		free (replace.ptr);
	input->pos += replace.len;
	input->last_expand_len = replace.len;
	return (err);
}

/**
 * @brief Handle special variables.
 *
 * '$?' expands to exit status of last exectued command.
 * Uses global variable g_status.
 * '$$' expands to current pid.
 * Is inserted at startup.
 * @param var Used for var.len
 * @param replace Where to save replace string.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_special_dollar(t_str *var, t_str *replace, t_hashtable *symtab, char c)
{
	t_env_var	*env_var;

	var->len = 1;
	if (c == '?')
	{
		replace->ptr = ft_itoa(g_status);
		if (!replace->ptr)
			return (ERR_MALLOC);
		replace->len = ft_strlen(replace->ptr);
	}
	else if (c == '$')
	{
		env_var = ft_hashtable_lookup(symtab, "$$", 2);
		if (!env_var)
			return (ERR_NOEXPAND);
		replace->ptr = ft_strdup(env_var->value);
		if (!replace->ptr)
			return (ERR_MALLOC);
		replace->len = ft_strlen(replace->ptr);
	}
	return (SUCCESS);
}

/**
 * @brief Get variable var.
 *
 * Sets var.ptr to position after $ and var.len to 0
 * Calc the var.len:
 * As first char after $ only underscore and alphabetic are allowed.
 * After that underscore and alphanumeric are allowed.
 * In case of var.len 0: if a quote follows after $, $ is removed.
 * This is not the case for HEREDOC expansion which is checked with input.type.
 * Else $ is skipped.
 * @param input Pointer to tracker.
 * @param var Pointer to var struct.
 * @return t_err SUCCESS, ERR_NOEXPAND.
 */
t_err	ft_get_dollar_var(t_track *input, t_str *var)
{
	var->ptr = input->str + input->pos + 1;
	var->len = 0;
	if (var->ptr[var->len] == '_' || ft_isalpha(var->ptr[var->len]))
	{
		var->len++;
		while (var->ptr[var->len] == '_' || ft_isalnum(var->ptr[var->len]))
			var->len++;
	}
	if (var->len == 0)
	{
		if (input->type != HEREDOC && !input->quoted
			&& (input->str[input->pos + 1] == '\''
				|| input->str[input->pos + 1] == '"'))
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
 * @param var Pointer to var struct.
 * @param symtab Environment.
 * @param replace Pointer to struct where to save string.
 * @return t_err SUCCESS, ERR_MALLOC.
 */
t_err	ft_get_dollar_replace(t_str *var, t_hashtable *symtab, t_str *replace)
{
	t_env_var	*env_var;

	env_var = ft_hashtable_lookup(symtab, var->ptr, var->len);
	if (!env_var)
		replace->ptr = ft_strdup("");
	else
		replace->ptr = ft_strdup(env_var->value);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
	return (SUCCESS);
}
