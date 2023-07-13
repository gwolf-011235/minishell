/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:14 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/13 22:20:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"expander.h"

t_error	ft_get_tilde_replace(char *token, t_hashtable *symtab, char **replace)
{
	char		*target;
	t_env_var	*env_var;

	if (!ft_strcmp(token, "~"))
		target = "HOME";
	else if (!ft_strcmp(token, "~+"))
		target = "PWD";
	else if (!ft_strcmp(token, "~-"))
		target = "OLDPWD";
	env_var = ft_hashtable_lookup(symtab, target, ft_strlen(target));
	if (!env_var)
		return (ERR_NOT_FOUND);
	*replace = ft_strdup(env_var->value);
	if (!*replace)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_error	ft_get_tilde_token(char *input, size_t pos, char **token)
{
	*token = "~";
	pos++;
	if (input[pos] == '+')
	{
		*token = "~+";
		pos++;
	}
	else if (input[pos] == '-')
	{
		*token = "~-";
		pos++;
	}
	if (input[pos] != '\\' && input[pos] != '\0')
		*token = NULL;
	return (SUCCESS);
}

t_error	ft_expand_tilde(char **input, t_hashtable *symtab, size_t *pos)
{
	char	*token;
	char	*replace;
	size_t	replace_len;
	t_error	err;

	if (*pos != 0 && (*input)[*pos - 1] != '=')
		return (SUCCESS);
	token = NULL;
	ft_get_tilde_token(*input, *pos, &token);
	if (!token)
		return (SUCCESS);
	replace = NULL;
	err = ft_get_tilde_replace(token, symtab, &replace);
	if (err == ERR_NOT_FOUND)
		return (SUCCESS);
	if (err != SUCCESS)
		return (err);
	replace_len = ft_strlen(replace);
	err = ft_insert_replace(input, *pos, token, replace);
	free(replace);
	if (err != SUCCESS)
		return (err);
	*pos += replace_len;
	return (SUCCESS);
}
