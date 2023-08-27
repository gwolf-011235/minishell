/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_libft_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:56:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 18:35:45 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_libft_wrapper.c
 * @brief Wrapper functions to print error messages with perror for libft.
 */
#include "minishell_error.h"

/**
 * @brief Wrapper function for ft_strdup to print error.
 * 
 * @param src 		Source string to be duplicated.
 * @param dst		Destination string to be created.
 * @param msg		Message for perror.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_err_strdup(const char *src, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_strdup(src);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for ft_itoa to print error.
 * 
 * @param n 		Integer to be transformed to string.
 * @param dst		Destination string to be created.
 * @param msg		Message for perror.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_err_itoa(int n, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_itoa(n);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

/**
 * @brief Wrapper function for ft_strjoin to print error.
 * 
 * @param s1		String to which to append.
 * @param s2		String to be joined.
 * @param dst		Destination string to be created.
 * @param msg		Message for perror.
 * @return t_err 	ERR_MALLOC, SUCCESS
 */
t_err	ft_err_strjoin(const char *s1, const char *s2, char **dst, char *msg)
{
	errno = 0;
	*dst = ft_strjoin(s1, s2);
	if (*dst == NULL)
	{
		perror(msg);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}
