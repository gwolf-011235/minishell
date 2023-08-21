/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:04:02 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/21 17:47:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_err	ft_startup(t_data *data)
{
	t_err	err;

	ft_init_data(data);

}

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
	data->loop = true;
}
