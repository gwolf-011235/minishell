/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:07:40 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/01 16:44:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	ft_get_token_replacement(char **replacement, char target, t_hashtable sym_tab)
{
	static const t_replace_ptr	look_up_tab[128] = {
	['h'] = ft_prompt_replace_h,
	['n'] = ft_prompt_replace_n,
	['u'] = ft_prompt_replace_u,
	['r'] = ft_prompt_replace_r,
	['w'] = ft_prompt_replace_w
	};

	if (!replacement || !target || !sym_tab)
		return (ERR_EMPTY);
	return(look_up_tab[target](replacement, sym_tab));
}

/**
 * @brief Assign corresponding token string.
 *
 * Token strings are defined in minishell.h.
 *
 * @param token Where to assign string.
 * @param target Which string shall be assigned.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_OUT_OF_BOUNDS,
 * ERR_WRONG_TOKEN
 */
t_error	ft_get_token(char **token, unsigned char target)
{
	static const char	*look_up_tab[128] = {
	['h'] = PROMPT_EXPAND_H,
	['n'] = PROMPT_EXPAND_N,
	['u'] = PROMPT_EXPAND_U,
	['r'] = PROMPT_EXPAND_R,
	['w'] = PROMPT_EXPAND_W
	};

	if (!token || !target)
		return (ERR_EMPTY);
	if (target > 127)
		return (ERR_OUT_OF_BOUNDS);
	if (look_up_tab[target])
		*token = (char *)look_up_tab[target];
	else
		return (ERR_WRONG_TOKEN);
	return (SUCCESS);
}

/**
 * @brief Search string for occurence of token.
 *
 * First searches for backslash.
 * If backslash is found the following character is
 *
 * @param ps_string
 * @param token
 * @return t_error
 */
t_error	ft_search_token(const char *ps_string, char **token)
{
	char	*target;
	t_error	err;

	if (!ps_string || !token)
		return (ERR_EMPTY);
	target = ft_strchr(ps_string, '\\');
	if (!target)
		return (SUCCESS);
	target++;
	if (!*target)
	{
		printf("Empty backslash\n");
		return (ERR_WRONG_TOKEN);
	}
	if (!ft_strchr(PROMPT_EXPAND_SUPPORTED, *target))
	{
		printf("Not recognised: \\%c\n", *target);
		return (ERR_WRONG_TOKEN);
	}
	err = ft_get_token(token, target);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}

/**
 * @brief Expands the provided prompt string.
 *
 * In infinite loop:
 * Search for recognized token with ft_search_token().
 * Create replacement with ft_get_token_replacement().
 * Replace token with ft_replace_token().
 * If no token is found (anymore) break out.
 *
 * @param prompt This gets searched and expanded.
 * @param sym_tab Symbols which can are used to expand.
 * @return t_error SUCCESS, ERR_EMPTY, ERR_MALLOC
 */
t_error	ft_expand_prompt_str(char **prompt, t_hashtable sym_tab)
{
	t_error	err;
	char	*token;
	char	*replacement;

	if (!prompt || !sym_tab)
		return (ERR_EMPTY);
	token = NULL;
	replacement = NULL;
	while (1)
	{
		err = ft_search_token(*prompt, &token);
		if (err != SUCCESS)
			return (err);
		if (!token)
			return (SUCCESS);
		err = ft_get_token_replacement(&replacement, token + 1, sym_tab);
		if (err != SUCCESS)
			return (err);
		err = ft_replace_token(prompt, token, replacement);
		token = NULL;
		free(replacement);
		if (err != SUCCESS)
			return (err);
	}
}

/**
 * @brief Create a prompt string which gets expanded
 *
 * Search for provided var $PS1 or $PS2.
 * If not found create prompt with provided standard.
 * If found strdup value and expand it.
 *
 * @param sym_tab Symbol table where to search.
 * @param prompt Where to save the prompt.
 * @param ps Prompt string variable $PS1 or $PS2.
 * @param std Standard string if ps is not found.
 * @return t_error SUCCESS, ERR_MALLOC, ERR_EMPTY
 */
t_error	ft_create_prompt(t_hashtable sym_tab,
			char **prompt, char *ps, char *std)
{
	t_env_var	*env_var;
	t_error		err;

	env_var = ft_hashtable_lookup(sym_tab, ps);
	if (!env_var)
	{
		*prompt = ft_strdup(std);
		if (*prompt == NULL)
			return (ERR_MALLOC);
	}
	else
	{
		*prompt = ft_strdup(env_var->value);
		if (!*prompt)
			return (ERR_MALLOC);
		err = ft_expand_prompt_str(prompt, sym_tab);
		if (err != SUCCESS)
		{
			free(*prompt);
			return (err);
		}
	}
	return (SUCCESS);
}
