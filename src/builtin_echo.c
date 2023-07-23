/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:47:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/23 23:25:51 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_skip_n_flags(char **argv, size_t *i, bool *newline)
{
	while (argv[*i] && !ft_strncmp(argv[*i], "-n", ft_strlen(argv[*i])))
	{
		*newline = false;
		(*i)++;
	}
	return (SUCCESS);
}

t_err	ft_write_args(char **argv, size_t *i)
{
	while (argv[*i])
	{
		ft_putstr_fd(argv[*i], 1);
		if (argv[*i + 1] && argv[*i][0] != '\0')
			write(1, " ", 1);
		(*i)++;
	}
	return (SUCCESS);
}

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
