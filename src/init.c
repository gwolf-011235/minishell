/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:04:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/27 22:37:06 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes shell.
 *
 * Sets signal handlers.
 * Initialize data struct.
 * Import and check environment.
 * @param data Pointer to data struct.
 * @param argv_zero First argument of argv.
 */
void	ft_startup(t_data *data, char *argv_zero)
{
	ft_signal_setup(SIGINT, SIG_IGNORE);
	ft_signal_setup(SIGQUIT, SIG_IGNORE);
	ft_init_data(data);
	ft_env_setup(data->env_table, argv_zero, &data->buf);
}

/**
 * @brief Initilize data struct.
 *
 * Create hashtable.
 * Create buffer.
 * Init all other variables.
 * Handles all errors.
 * @param data Pointer to data struct.
 */
void	ft_init_data(t_data *data)
{
	errno = 0;
	data->env_table = ft_hashtable_create(HASHTABLE_SIZE, ft_hash_fnv1);
	if (!data->env_table)
	{
		perror("minishell: ft_init_data");
		ft_putendl_fd("minishell: fata error at startup. I'm giving up.", 2);
		exit(1);
	}
	if (ft_buf_init(&data->buf) != SUCCESS)
	{
		ft_hashtable_destroy(data->env_table);
		ft_putendl_fd("minishell: fata error at startup. I'm giving up.", 2);
		exit(1);
	}
	data->prompt1 = NULL;
	data->prompt2 = NULL;
	data->loop = true;
	data->free_prompt = true;
}

/**
 * @brief Creates prompt string PS1 and PS2
 *
 * Create prompt with ft_prompt_create().
 * If any of the two prompt creation fails, set free_prompt to false.
 * Handles all errors.
 * @param env_table Environment.
 * @param prompt1 Where to save prompt PS1.
 * @param prompt2 Where to save prompt PS2.
 * @param free_prompt Bool to set if prompt needs to be freed.
 */
void	ft_create_prompts(t_data *data)
{
	t_err	err;

	data->free_prompt = true;
	err = ft_prompt_create(data->env_table, &data->prompt1, "PS1", PS1_STD);
	if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: warning: could not create prompts.", 2);
	if (err != SUCCESS)
	{
		data->free_prompt = false;
		data->prompt2 = PS2_STD;
	}
	if (data->free_prompt)
	{
		err = ft_prompt_create(data->env_table, &data->prompt2, "PS2", PS2_STD);
		if (err == ERR_MALLOC)
			ft_putendl_fd("minishell: warning: could not create prompts.", 2);
		if (err != SUCCESS)
		{
			data->free_prompt = false;
			free(data->prompt1);
			data->prompt1 = PS1_STD;
		}
	}
}
