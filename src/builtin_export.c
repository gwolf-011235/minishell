/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 11:36:13 by gwolf            ###   ########.fr       */
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

t_err	ft_check_and_insert(char *str, t_hashtable *env_tab)
{
	size_t	keylen;
	t_err	err;
	char	*temp;

	keylen = 0;
	err = ft_get_env_keylen(str, &keylen);
	if (err != SUCCESS)
		return (err);
	temp = ft_strdup(str);
	if (!temp)
		return (ERR_MALLOC);
	err = ft_insert_env_var(env_tab, temp, keylen);
	if (err != SUCCESS)
	{
		free(temp);
		return (err);
	}
	return (SUCCESS);
}

t_err	ft_export(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	size_t	i;

	size = 0;
	err = ft_get_array_size(argv, &size);
	if (size == 1)
	{
		//ft_print_sorted();
		return (SUCCESS);
	}
	i = 1;
	while (argv[i])
	{
		err = ft_check_and_insert(argv[i], env_tab);
		if (err != SUCCESS)
			ft_export_error(err, argv[i]);
		i++;
	}
	return (SUCCESS);
}

//export can export multiple vars
//try for every var even if something in the middle doesn't work