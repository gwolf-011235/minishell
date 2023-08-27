/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:32:57 by sqiu              #+#    #+#             */
/*   Updated: 2023/08/27 18:19:59 by sqiu             ###   ########.fr       */
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

/**
 * @brief Cleans input, both prompts and env after each loop.
 * 
 * @param input Input string.
 * @param data 	Data struct containing env.
 */
void	ft_clean_after_loop(char **input, t_data *data)
{
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	if (data->free_prompt)
	{
		free(data->prompt1);
		data->prompt1 = NULL;
		free(data->prompt2);
		data->prompt2 = NULL;
	}
	ft_envp_destroy(&data->envp);
}

/**
 * @brief Final cleanup on exiting.
 * 
 * Frees input, both prompts and env.
 * Frees hashtable.
 * Frees buffer.
 * Cleans the history of readline.
 * Only if is a tty, print exit.
 * @param input Input string.
 * @param data 	Data struct containing env.
 */
void	ft_clean_on_exit(char **input, t_data *data)
{
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	if (data->free_prompt)
	{
		free(data->prompt1);
		data->prompt1 = NULL;
		free(data->prompt2);
		data->prompt2 = NULL;
	}
	ft_envp_destroy(&data->envp);
	ft_hashtable_destroy(data->env_table);
	ft_buf_destroy(&data->buf);
	clear_history();
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", 2);
}
