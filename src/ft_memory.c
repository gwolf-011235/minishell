/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:22:36 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/04 10:48:02 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Simple implementation of realloc.
 *
 * If pointer and new size are empty, NULL is returned.
 * If new size is 0 the old pointer gets free'd.
 * If the pointer is NULL, it gets malloc'd with size.
 * Else a new pointer is malloc'd and memcpy'd.
 *
 * @param ptr The ptr to the memory to realloc.
 * @param new_size The new memory block size.
 * @param curr_size The old memory block size.
 * @return void* New malloc'd and memcpy'd pointer, NULL if fail.
 */
void	*ft_realloc(void *ptr, size_t new_size, size_t curr_size)
{
	void	*new_ptr;

	if (ptr == NULL && new_size == 0)
		return (NULL);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr != NULL)
	{
		if (curr_size != 0)
			ft_memcpy(new_ptr, ptr, curr_size);
		free(ptr);
	}
	return (new_ptr);
}