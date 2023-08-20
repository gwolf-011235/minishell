/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:24:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/15 09:29:59 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_utils.c
 * @brief Helper functions for builtins.
 */
#include "mod_builtin.h"

/**
 * @brief Calc the size of an NULL terminated array.
 *
 * @param array NULL terminated array.
 * @param size Where to save the size.
 * @return t_err SUCCESS
 */
void	ft_get_array_size(char **array, size_t *size)
{
	while (array[*size])
		(*size)++;
}

/**
 * @brief Calc the keylen of an environment var.
 *
 * First char has to be alphabetical or underscore.
 * Following chars can also include numbers.
 * The char following the key has to be '=' if assigned a value.
 * Or zero terminator if no value.
 * @param str Env_str to check
 * @param len Where to save the len.
 * @return t_err SUCCESS, ERR_INVALID_NAME.
 */
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

/**
 * @brief Insert or swap the given env_str.
 *
 * Search for the env var.
 * If found swap it with the new one.
 * If not found insert it.
 * @param env_tab Environment.
 * @param env_str New environment string.
 * @param keylen Length of the variable key.
 * @return t_err SUCCESS, ERR_EMPTY, ERR_MALLOC, ERR_HT_NO_SWAP,
 * ERR_HT_NO_INSERT.
 */
t_err	ft_update_env_var(t_hashtable *env_tab,
		char *env_str, size_t keylen, bool has_value)
{
	t_env_var	*env_var;
	t_err		err;

	env_var = ft_hashtable_lookup(env_tab, env_str, keylen);
	if (env_var)
		err = ft_hashtable_swap(env_tab, env_str, keylen, has_value);
	else
		err = ft_hashtable_insert(env_tab, env_str, keylen, has_value);
	return (err);
}

/**
 * @brief Swap two string pointers.
 *
 * @param str1 First string.
 * @param str2 Second string.
 */
void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

/**
 * @brief Quicksort a string array.
 *
 * Implements the quicksort algorithm.
 * Starting pivot_index low is zero, first element of array is pivot.
 * Divides the array in sub-arrays around the pivot.
 * String are compared using ft_strncmp() and then swapped if needed.
 * Gets called recursively until all sub-arrays are sorted.
 * @param arr Array to be sorted.
 * @param low Starting index.
 * @param high Endinf index.
 */
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
