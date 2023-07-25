/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/25 13:01:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_builtin.h"

t_err	ft_get_array_size(char **array, size_t *size)
{
	if (!array || !size)
		return (ERR_EMPTY);
	while (array[*size])
		(*size)++;
	return (SUCCESS);
}

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

t_err	ft_update_env_var(t_hashtable *env_tab, char *env_str, size_t keylen)
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
