/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:07:40 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/31 18:45:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	ft_get_token_replacement(char **replacement, char target)
{
	static const t_replace_ptr	look_up_tab[128] = {
	['h'] =
	['n'] =
	['u'] =
	};
}

t_error	ft_get_token(char **token, char target)
{
	static const char	*look_up_tab[128] = {
	['h'] = "\\h",
	['n'] = "\\n",
	['u'] = "\\u"
	};

	if (!token || !target)
		return (ERR_EMPTY);
	if (target > 127)
		return (ERR_OUT_OF_BOUNDS);
	*token = look_up_tab[target];
	return (SUCCESS);
}

t_error	ft_search_token(const char *ps_string, char **token)
{
	char	target;
	t_error	err;

	if (!ps_string || !token)
		return (ERR_EMPTY);
	target = ft_strchr(ps_string, '\\');
	while (*ps_string && !target)
	{
		ps_string++;
		target = ft_strchr(ps_string, '\\');
	}
	if (!target || !*(ps_string + 1))
		return (SUCCESS);
	if (ft_strchr("hnu", target))
		err = ft_get_token(token, target);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

t_error	ft_expand_prompt_str(char **prompt, const char *ps_string)
{
	t_error	err;
	char	*token;
	char	*replacement;

	token = NULL;
	while (1)
	{
		err = ft_search_token(ps_string, &token);
		if (err != SUCCESS)
			return (err);
		if (!token)
			return (SUCCESS);
		ft_get_token_replacement(&replacement, token + 1);
		//replace string
		//free replacement
	}
}

t_error	ft_create_prompt(t_hashtable sym_tab, char **prompt, char *ps, char *std)
{
	t_env_var	env_var;
	t_error		error;

	env_var = ft_hashtable_lookup(sym_tab, ps);
	if (!env_var)
	{
		*prompt = ft_strdup(std);
		if (*prompt == NULL)
			return (ERR_MALLOC);
	}
	else
	{
		error = ft_expand_prompt_str(prompt, env_var->value);
		if (error != SUCCESS)
			return (error);
	}
}
