/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:47:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 17:11:47 by gwolf            ###   ########.fr       */
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
 *
 * @param argv NULL terminated args.
 * @return t_err SUCCESS, ERR_EMPTY
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
	err = ft_get_array_size(argv, &size);
	if (err != SUCCESS)
		return (err);
	if (size > 1)
	{
		ft_skip_n_flags(argv, &i, &newline);
		ft_write_args(argv, &i);
	}
	if (newline == true)
		write (1, "\n", 1);
	return (SUCCESS);
}

/**
 * @brief Skip over all -n flags
 *
 * Increment the passed i as long as an "-n" string is found.
 * It's possible to pass several -n flags even though they have no
 * additional effect.
 * If at least one -n flag is found, set bool newline to false.
 *
 * @param argv NULL terminated args.
 * @param i Pointer to current index of array.
 * @param newline Pointer to bool which can get switched.
 * @return t_err SUCCESS
 */
t_err	ft_skip_n_flags(char **argv, size_t *i, bool *newline)
{
	while (argv[*i] && !ft_strncmp(argv[*i], "-n", ft_strlen("-n")))
	{
		*newline = false;
		(*i)++;
	}
	return (SUCCESS);
}

/**
 * @brief Write all args in array.
 *
 * Write arg at index i.
 * If there is another arg, write a space.
 *
 * @param argv NULL temrinated args.
 * @param i Pointer to current index of array.
 * @return t_err SUCCESS
 */
t_err	ft_write_args(char **argv, size_t *i)
{
	while (argv[*i])
	{
		ft_putstr_fd(argv[*i], 1);
		if (argv[*i + 1])
			ft_putchar_fd(' ', 1);
		(*i)++;
	}
	return (SUCCESS);
}

