/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 11:34:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_tilde.c
 * @brief Functions to handle expansion of tilde.
 */
#include "mod_expand.h"

/**
 * @brief Expand a tilde char to corresponding environment var.
 *
 * If position is not 0 or the char before is not '=' return.
 * Check if recognised token (~, ~+, ~-).
 * Get the replacement for the found token.
 * Insert the replacement in the string.
 * Update the position to be after the inserted string.
 * @param input Pointer to tracker.
 * @param symtab Environment.
 * @return t_err SUCCESS, ERR_NOEXPAND, ERR_MALLOC.
 */
t_err	ft_expand_tilde(t_track *input, t_hashtable *symtab)
{
	t_str	token;
	t_str	replace;
	t_err	err;

	if (input->pos != 0 && input->str[input->pos - 1] != '=')
		return (ERR_NOEXPAND);
	token.ptr = NULL;
	err = ft_get_tilde_token(input, &token);
	if (err != SUCCESS)
		return (err);
	replace.ptr = NULL;
	err = ft_get_tilde_replace(token, symtab, &replace, &input->pos);
	if (err == ERR_NOT_FOUND)
		return (ERR_NOEXPAND);
	if (err != SUCCESS)
		return (err);
	err = ft_insert_replace(input, token, replace);
	free(replace.ptr);
	if (err != SUCCESS)
		return (err);
	input->pos += replace.len;
	return (SUCCESS);
}

/**
 * @brief Check for a recognised token.
 *
 * At first the string "~" is assigned.
 * If '+' or '-' is found increase position and reassign
 * Then a '/' or a '\0' has to be found, else the string is set to NULL.
 * Also if not found increase tracker position to jump over the '~'.
 * Calc the token.len.
 * @param input Pointer to tracker.
 * @param token Where to save the token.
 * @return t_err SUCCESS, ERR_NOEXPAND.
 */
t_err	ft_get_tilde_token(t_track *input, t_str *token)
{
	size_t	i;

	i = input->pos;
	token->ptr = "~";
	i++;
	if (input->str[i] == '+')
		token->ptr = "~+";
	else if (input->str[i] == '-')
		token->ptr = "~-";
	if (input->str[i] == '+' || input->str[i] == '-')
		i++;
	if (input->str[i] != '/' && input->str[i] != '\0')
	{
		input->pos++;
		return (ERR_NOEXPAND);
	}
	else
		token->len = ft_strlen(token->ptr);
	return (SUCCESS);
}

/**
 * @brief Find the corresponding replacement for token.
 *
 * Depending on the token find env var.
 * ~ = $HOME.
 * ~+ = $PWD.
 * ~- = $OLDPWD.
 * If not found increase tracker position to account for '~' and
 * return ERR_NOT_FOUND.
 * If found ft_strdup() the value.
 * Calc replace.len.
 * @param token Contains searched for token.
 * @param symtab Environment.
 * @param replace Where to save replace string.
 * @param pos Current position.
 * @return t_err SUCCESS, ERR_NOT_FOUND, ERR_MALLOC
 */
t_err	ft_get_tilde_replace(t_str token, t_hashtable *symtab, t_str *replace, size_t *pos)
{
	char		*target;
	t_env_var	*env_var;

	if (!ft_strncmp(token.ptr, "~", 2))
		target = "HOME";
	else if (!ft_strncmp(token.ptr, "~+", 3))
		target = "PWD";
	else if (!ft_strncmp(token.ptr, "~-", 3))
		target = "OLDPWD";
	env_var = ft_hashtable_lookup(symtab, target, ft_strlen(target));
	if (!env_var)
	{
		(*pos)++;
		return (ERR_NOT_FOUND);
	}
	replace->ptr = ft_strdup(env_var->value);
	if (!replace->ptr)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->ptr);
	return (SUCCESS);
}
