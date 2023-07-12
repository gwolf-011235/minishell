/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:46:44 by sqiu              #+#    #+#             */
/*   Updated: 2023/07/12 22:04:51 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_tok_utils.h"

/**
 * @brief Initiate token by reserving 1 Byte of memory space.
 * 
 * @param data 		Struct containing the token.
 * @return t_error	ERR_MALLOC, SUCCESS
 */
t_error	ft_init_tok(t_data *data)
{
	data->token.tok = malloc(1);
	if (!data->token.tok)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/**
 * @brief Free token string.
 * 
 * @param token Token to be freed.
 */
void	ft_free_tok(t_tok *token)
{
	if (token->tok)
		free(token->tok);
}

/**
 * @brief Add character to buffer string.
 * 
 * In case the buffer string is not long enough, its size is doubled.
 * @param c 		Character to be added.
 * @param buf 		Buffer string.
 * @param buf_size 	Buffer string length.
 * @param buf_pos 	Current position in buffer string.
 * @return t_error 	ERR_MALLOC, SUCCESS
 */
t_error	ft_add_to_buf(char c, char *buf, int *buf_size, int *buf_pos)
{
	char	*tmp;

	buf[*buf_pos] = c;
	(*buf_pos)++;
	if (*buf_pos >= *buf_size)
	{
		tmp = ft_realloc(buf, (*buf_size * 2), *buf_size);
		if (!tmp)
			return (ERR_MALLOC);
		buf = tmp;
		*buf_size *= 2;
	}
	return (SUCCESS);
}
