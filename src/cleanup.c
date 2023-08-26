/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:32:57 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/26 16:59:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleanup.c
 * @brief General functions to clean up the program.
 */

#include "mod_cleanup.h"

/**
 * @brief Frees a NULL-terminated string array and its strings.
 *
 * @param arr String array to be freed.
 */
void	ft_free_str_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_clean_after_loop(char *input, t_data *data)
{
	free(input);
	if (data->free_prompt)
	{
		free(data->prompt1);
		data->prompt1 = NULL;
		free(data->prompt1);
		data->prompt2 = NULL;
	}
	ft_envp_destroy(&data->envp);
}

void	ft_clean_on_exit(t_data *data)
{
	ft_hashtable_destroy(data->env_table);
	ft_buf_destroy(&data->buf);
	clear_history();
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", 2);
}
