/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:43:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 15:42:44 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_is_number(char *str)
{
	size_t	i;

	if (!str)
		return (ERR_EMPTY);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERR_NONUM);
		i++;
	}
	return (SUCCESS);
}

t_err	ft_exit(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	int		ret_code;

	size = 0;
	ret_code = 255;
	err = ft_get_array_size(argv, &size);
	ft_putendl_fd("exit", 2);
	if (size >= 2)
		err = ft_is_number(argv[1]);
	if (err != SUCCESS)
	{
		ft_exit_error(err, argv[1]);
		ret_code = 2;
	}
	else if (size == 2)
		ret_code = ft_atoi(argv[1]);
	else if (size > 2)
	{
		ret_code = 1;
		return (ft_exit_error(ERR_EXIT, NULL));
	}
	ft_hashtable_destroy(env_tab);
	exit(ret_code);
}
