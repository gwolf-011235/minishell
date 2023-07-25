/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 12:48:39 by gwolf            ###   ########.fr       */
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

void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void	ft_quicksort_strings(char **arr, int low, int high)
{
	int		pivot_idx;
	char	*pivot_value;
	int		i;

	pivot_idx = low;
	pivot_value = arr[pivot_idx];
	if (low < high)
	{
		i = low + 1;
		while (i <= high)
		{
			if (ft_strncmp(arr[i], pivot_value, ft_strlen(pivot_value)) < 0)
			{
				pivot_idx++;
				ft_swap(&arr[i], &arr[pivot_idx]);
			}
			i++;
		}
		ft_swap(&arr[low], &arr[pivot_idx]);
		ft_quicksort_strings(arr, low, pivot_idx - 1);
		ft_quicksort_strings(arr, pivot_idx + 1, high);
	}
}

t_err	ft_pretty_print_envp(char **envp, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	keylen;
	t_err	err;

	i = 0;
	while (i < size)
	{
		keylen = 0;
		err = ft_get_env_keylen(envp[i], &keylen);
		if (err != SUCCESS)
			return (err);
		ft_putstr_fd("export ", 1);
		j = 0;
		while (j < keylen)
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if (envp[i][keylen] == '=')
			printf("=\"%s\"", envp[i] + keylen + 1);
		printf("\n");
		i++;
	}
	return (SUCCESS);
}

t_err	ft_print_env_sorted(t_hashtable *env_tab)
{
	char	**envp;
	t_err	err;

	envp = NULL;
	err = ft_envp_create(env_tab, &envp);
	if (err != SUCCESS)
		return (ft_export_error(err, NULL));
	ft_quicksort_strings(envp, 0, env_tab->num_elements - 1);
	err = ft_pretty_print_envp(envp, env_tab->num_elements);
	return (err);
}

t_err	ft_export(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	size_t	i;

	size = 0;
	err = ft_get_array_size(argv, &size);
	if (size == 1)
		return (ft_print_env_sorted(env_tab));
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
