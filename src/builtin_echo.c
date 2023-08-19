/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:47:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 09:49:28 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_echo.c
 * @brief Implementation of builtin echo.
 */
#include "mod_builtin.h"

/**
 * @brief Print the given args on standard output.
 *
 * Check the size with ft_get_array_size().
 * Skip over -n flags with ft_skip_n_flags().
 * Write all remaining args with ft_write_args().
 * Only print newline if no -n flags was encountered.
 * @param argv NULL terminated args.
 * @return t_err SUCCESS, ERR_WRITE
 */
t_err	ft_echo(char **argv)
{
	size_t	i;
	bool	newline;
	size_t	size;
	t_err	err;

	i = 1;
	newline = true;
	size = 0;
	err = SUCCESS;
	ft_get_array_size(argv, &size);
	if (size > 1)
	{
		ft_skip_n_flags(argv, &i, &newline);
		err = ft_write_args(argv, &i);
		if (err != SUCCESS)
			return (err);
	}
	if (newline == true)
		err = ft_err_write(1, "\n", "minishell: echo");
	if (err != SUCCESS)
		g_status = 1;
	else
		g_status = 0;
	return (err);
}

/**
 * @brief Skip over all -n flags
 *
 * Increment the passed i as long as an "-n" string is found.
 * It's possible to pass several -n flags even though they have no
 * additional effect.
 * If at least one -n flag is found, set bool newline to false.
 * @param argv NULL terminated args.
 * @param i Pointer to current index of array.
 * @param newline Pointer to bool which can get switched.
 */
void	ft_skip_n_flags(char **argv, size_t *i, bool *newline)
{
	while (argv[*i] && !ft_strncmp(argv[*i], "-n", 3))
	{
		*newline = false;
		(*i)++;
	}
}

/**
 * @brief Write all args in array.
 *
 * Write arg at index i.
 * If there is another arg, write a space.
 * If a write call fails, print error and set status
 * @param argv NULL temrinated args.
 * @param i Pointer to current index of array.
 * @return t_err SUCCESS, ERR_WRITE
 */
t_err	ft_write_args(char **argv, size_t *i)
{
	while (argv[*i])
	{
		errno = 0;
		ft_putstr_fd(argv[*i], 1);
		if (argv[*i + 1])
			ft_putchar_fd(' ', 1);
		(*i)++;
		if (errno != 0)
		{
			perror("minishell: echo");
			g_status = 1;
			return (ERR_WRITE);
		}
	}
	return (SUCCESS);
}
