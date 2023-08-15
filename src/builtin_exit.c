/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:43:10 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 09:32:02 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_exit.c
 * @brief Implementation of builtin exit.
 */
#include "mod_builtin.h"

/**
 * @brief Exit the current shell instance.
 *
 * Check size of given args.
 * If at least one arg is given check if it is a number with ft_is_number().
 * If not a number print error msg and set return code but continue.
 * If a exactly one number arg convert it with ft_atoi().
 * If arg1 is a number but more than one arg print error msg and return(!).
 * Free t_hashtable.
 * Call exit() with error code.
 * @param argv NULL terminated args.
 * @param env_tab Environment.
 * @return t_err ERR_EXIT
 * @todo Maybe restructure to not use exit() and handle t_err instead.
 * @todo If no arg is given should return exit status of last command - global?
 */
t_err	ft_exit(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	int		ret_code;

	size = 0;
	err = SUCCESS;
	ret_code = 0;
	ft_get_array_size(argv, &size);
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

/**
 * @brief Check if provided str is number.
 *
 * A single sign (+/-) is jumped over.
 * Iterate as long as current char is digit with ft_isdigit().
 * @param str String to check.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_NONUM
 */
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
