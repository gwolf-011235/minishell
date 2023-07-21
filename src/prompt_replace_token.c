/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_replace_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:03:52 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 13:55:56 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_prompt.h"

/**
 * @brief Calculates the len of the string, where tokens have been replaced.
 *
 * Check if either of the provided pointers is empty.
 * Calc the strlen of token and replacement.
 * Search for instances of token in string. If one is found add len upto token,
 * add replacement len, then jump over token. Search again.
 * If no token is found add remaining len of str.
 *
 * @param str The string for which the expanded len should be calculated.
 * @param token Char string which is going to be replaced.
 * @param replacement Char string as replacement for token.
 * @param expanded_len Pointer to size_t in which to save the len.
 * @return t_error ERR_EMPTY, SUCCESS
 */
t_err	ft_calc_replace_len(const char *str, const char *token,
		const char *replacement, size_t *expanded_len)
{
	size_t	token_len;
	size_t	replacement_len;
	char	*pos;

	if (!str || !*str || !token || !replacement || !expanded_len)
		return (ERR_EMPTY);
	token_len = ft_strlen(token);
	replacement_len = ft_strlen(replacement);
	pos = ft_strnstr(str, token, ft_strlen(str));
	while (pos != NULL)
	{
		*expanded_len += pos - str + replacement_len;
		str = pos + token_len;
		pos = ft_strnstr(str, token, ft_strlen(str));
	}
	*expanded_len += ft_strlen(str);
	return (SUCCESS);
}

/**
 * @brief Copies str into expanded_str while replacing each token.
 *
 * Check if either of the pointers is empty.
 * Search for token in str. If token is found, everything upto token is copied.
 * Then replacement is copied and pos jumps over token.
 * If no token is found copy the remaining str.
 *
 * @param expanded_str Pointer pointer to buffer wherein to copy.
 * @param str Pointer to str which gets copied and expanded.
 * @param token Char string which should be replaced.
 * @param replacement Char string which is inserted instead of token.
 * @return t_error SUCCESS, ERR_EMPTY
 */
t_err	ft_expand_str(char **expanded_str, const char *str,
		const char *token, const char *replacement)
{
	size_t	token_len;
	char	*pos;

	if (!expanded_str || !*expanded_str || !str || !token || !replacement)
		return (ERR_EMPTY);
	token_len = ft_strlen(token);
	pos = ft_strnstr(str, token, ft_strlen(str));
	while (pos != NULL)
	{
		ft_strncat(*expanded_str, str, pos - str);
		ft_strcat(*expanded_str, replacement);
		str = pos + token_len;
		pos = ft_strnstr(str, token, ft_strlen(str));
	}
	ft_strcat(*expanded_str, str);
	return (SUCCESS);
}

/**
 * @brief This function finds token in str and replaces it.
 *
 * Calculate expanded len of str.
 * Malloc a buffer which holds expanded len and zero terminate.
 * Copy str into buffer whereby each token is replaced.
 * Free str and update pointer to the expanded string.
 *
 * @param str Pointer pointer to char string which is expanded.
 * @param token Char string to search for.
 * @param replacement Char string which replaces token.
 * @return t_error SUCCESS, ERR_MALLOC, ERR_EMPTY
 */
t_err	ft_replace_token(char **str, const char *token, const char *replacement)
{
	size_t	expanded_len;
	char	*expanded_str;
	t_err	err;

	expanded_len = 0;
	err = ft_calc_replace_len(*str, token, replacement, &expanded_len);
	if (err != SUCCESS)
		return (err);
	expanded_str = malloc(expanded_len * sizeof(char) + 1);
	if (expanded_str == NULL)
		return (ERR_MALLOC);
	*expanded_str = '\0';
	err = ft_expand_str(&expanded_str, *str, token, replacement);
	if (err != SUCCESS)
	{
		free(expanded_str);
		return (err);
	}
	free(*str);
	*str = expanded_str;
	return (SUCCESS);
}
