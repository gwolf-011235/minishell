/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/24 14:10:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	data->env_table = ft_hashtable_create(HASHTABLE_SIZE, ft_hash_fnv1);
	if (ft_import_env(data) != SUCCESS)
		printf("NO");
	ft_hashtable_destroy(data->env_table);
	free(data);
}