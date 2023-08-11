/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:56:15 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/10 23:18:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

//Make BUF_SIZE small in minishell_config.h for easier testing

void	test_buffer(void)
{
	t_buf	buf;
	size_t	i;

	ft_buf_init(&buf);
	i = 0;
	while (i < 1000)
	{
		ft_buf_strlcpy(&buf, "This has 20 char len", 21);
		i++;
	}
}

