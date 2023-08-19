/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:43:24 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/17 10:41:51 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file syntax_check.c
 * @brief Check input string for correct syntax
 */
#include "mod_syntax.h"

/**
 * @brief Jump over a quoted part of input.
 *
 * Search for another instance of the checked quote symbol.
 * If not found return syntax error.
 * If found add to i the len of quoted part.
 *
 * @param quote_start Pointer to start of quoted part.
 * @param i Pointer to i of ft_check_syntax().
 * @param target Either " or ' quote.
 * @return t_err
 */
t_err	ft_quote_skipper(const char *quote_start, size_t *i, char target)
{
	char	*quote_end;

	quote_end = ft_strchr((quote_start + 1), target);
	if (!quote_end)
	{
		printf(SYNTAX_QUOTE, target);
		return (ERR_SYNTAX);
	}
	*i += quote_end - quote_start;
	return (SUCCESS);
}

/**
 * @brief Check syntax for pipe '|' symbol.
 *
 * If pipe is the first symbol in input then error.
 * If next char is pipe symbol then error (no '||' allowed).
 * If pipe is last symbol in input then error.
 *
 * @param input Start of input string.
 * @param pos Position of checked pipe in input.
 * @return t_err SUCCESS, ERR_SYNTAX.
 */
t_err	ft_check_pipe(const char *input, size_t pos)
{
	size_t	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (i == pos)
	{
		printf(SYNTAX_TOKEN, input[pos]);
		return (ERR_SYNTAX);
	}
	i = pos + 1;
	if (input[i] == '|')
	{
		printf(SYNTAX_TOKEN, input[pos]);
		return (ERR_SYNTAX);
	}
	while (ft_isspace(input[pos]))
		i++;
	if (input[i] == '\0')
	{
		printf(SYNTAX_TOKEN, input[pos]);
		return (ERR_SYNTAX);
	}
	return (SUCCESS);
}

/**
 * @brief Check syntax for redirect '<' and '>' symbols
 *
 * Allows one occurrence of same symbol (i.e. << or >>).
 * Skips over space between symbol and next char.
 * If next char is '\0', '|', '<' or '>'.
 *
 * @param input Start of input string.
 * @param pos Position of checked redirect in input.
 * @param symbol Either '<' or '>'.
 * @return t_err SUCCESS, ERR_SYNTAX
 */
t_err	ft_check_redirect(const char *input, size_t pos, char symbol)
{
	size_t	i;

	i = pos + 1;
	if (input[i] == symbol && input[i + 1] != symbol)
		i++;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
	{
		printf(SYNTAX_NL);
		return (ERR_SYNTAX);
	}
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
	{
		printf(SYNTAX_TOKEN, input[i]);
		return (ERR_SYNTAX);
	}
	return (SUCCESS);
}

/**
 * @brief Check input string for syntax errors.
 *
 * Jump over quotes with ft_quote_skipper().
 * Check syntax for | with ft_check_pipe().
 * Check syntax for < and > ft_check_redirect()
 *
 * @param input Input string from readline.
 * @return t_err SUCCESS, ERR_SYNTAX
 */
t_err	ft_check_syntax(const char *input)
{
	t_err	err;
	size_t	i;

	err = SUCCESS;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '"' || input[i] == '\'')
			err = ft_quote_skipper(&input[i], &i, input[i]);
		else if (input[i] == '|')
			err = ft_check_pipe(input, i);
		else if (input[i] == '<' || input[i] == '>')
			err = ft_check_redirect(input, i, input[i]);
		if (err != SUCCESS)
			return (err);
		i++;
	}
	if (i == 0)
		return (ERR_NO_INPUT);
	return (SUCCESS);
}
