/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 10:37:10 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_get_env_keylen(char *str, size_t *len)
{
	if (!ft_isalpha(str[*len]) && str[*len] != '_')
		return (ERR_INVALID_NAME);
	while (ft_isalnum(str[*len]) || str[*len] == '_')
		(*len)++;
	if (str[*len] != '=' && str[*len] != '\0')
		return (ERR_INVALID_NAME);
	return (SUCCESS);
}

t_err	ft_insert_env_var(t_hashtable *env_tab, char *env_str, size_t keylen)
{
	t_env_var	*env_var;
	t_err		err;

	env_var = ft_hashtable_lookup(env_tab, env_str, keylen);
	if (env_var)
		err = ft_hashtable_swap(env_tab, env_str, keylen);
	else
		err = ft_hashtable_insert(env_tab, env_str, keylen);
	return (err);
}

t_err	ft_export(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	size_t	i;
	size_t	keylen;

	size = 0;
	err = ft_get_array_size(argv, &size);
	if (size == 1)
	{
		//ft_print_sorted();
		return (SUCCESS);
	}
	i = 0;
	while (argv[++i])
	{
		keylen = 0;
		err = ft_get_env_keylen(argv[i], &keylen);
		if (err != SUCCESS)
		{
			ft_export_error(err, argv[i]);
			continue ;
		}
		err = ft_insert_env_var(env_tab, argv[i], keylen);
		if (err != SUCCESS)
			ft_export_error(err, argv[i]);
	}
	return (SUCCESS);
}

//export can export multiple vars
//try for every var even if something in the middle doesn't work