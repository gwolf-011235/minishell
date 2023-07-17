/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/17 20:10:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_tilde.c
 * @brief Functions to handle expansion of tilde.
 */
#include	"expander.h"

/**
 * @brief Find the corresponding replacement for token.
 *
 * Depending on the token find env var.
 * ~: $HOME.
 * ~+: $PWD.
 * ~-: $OLDPWD.
 * If not found increase update position to account for '~' and
 * return ERR_NOT_FOUND.
 * If found ft_strdup() the value.
 * Calc replace.len.
 *
 * @param token Contains searched for token.
 * @param symtab Environment.
 * @param replace Where to save replace string.
 * @param pos Current position.
 * @return t_error SUCCESS, ERR_NOT_FOUND, ERR_MALLOC
 */
t_error	ft_get_tilde_replace(t_str_info token, t_hashtable *symtab, t_str_info *replace, size_t *pos)
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
	{
		(*pos)++;
		return (ERR_NOT_FOUND);
	}
	replace->str = ft_strdup(env_var->value);
	if (!replace->str)
		return (ERR_MALLOC);
	replace->len = ft_strlen(replace->str);
	return (SUCCESS);
}

/**
 * @brief Check for a recognised token.
 *
 * At first the string "~" is assigned.
 * If '+' or '-' is found increase position and reassign
 * Then a '/' or a '\0' has to be found, else the string is set to NULL.
 * Also if not found increase the position to jump over the '~'.
 * Calc the token.len.
 *
 * @param input String.
 * @param pos Current position.
 * @param token Where to save the token.
 * @return t_error SUCCESS, ERR_NOEXPAND.
 */
t_error	ft_get_tilde_token(char *input, size_t *pos, t_str_info *token)
{
	size_t	i;

	i = *pos;
	token->str = "~";
	i++;
	if (input[i] == '+')
		token->str = "~+";
	else if (input[i] == '-')
		token->str = "~-";
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (input[i] != '/' && input[i] != '\0')
	{
		(*pos)++;
		return (ERR_NOEXPAND);
	}
	else
		token->len = ft_strlen(token->str);
	return (SUCCESS);
}

/**
 * @brief Expand a tilde char to corresponding environment var.
 *
 * If position is not 0 or the char before is not '=' return.
 * Check if recognised token (~, ~+, ~-).
 * Get the replacement for the found token.
 * Insert the replacement in the string.
 * Update the position to be after the inserted string.
 *
 * @param input String.
 * @param symtab Environment.
 * @param pos Current position.
 * @return t_error SUCCESS, ERR_NOEXPAND, ERR_MALLOC.
 */
t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos)
{
	t_str_info	token;
	t_str_info	replace;
	t_error		err;

	if (*pos != 0 && (*input)[*pos - 1] != '=')
		return (ERR_NOEXPAND);
	token.str = NULL;
	err = ft_get_tilde_token(*input, pos, &token);
	if (err != SUCCESS)
		return (err);
	replace.str = NULL;
	err = ft_get_tilde_replace(token, symtab, &replace, pos);
	if (err == ERR_NOT_FOUND)
		return (ERR_NOEXPAND);
	if (err != SUCCESS)
		return (err);
	err = ft_insert_replace(input, *pos, token, replace);
	free(replace.str);
	if (err != SUCCESS)
		return (err);
	*pos += replace.len;
	return (SUCCESS);
}
