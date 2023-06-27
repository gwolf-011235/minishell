/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:13:28 by sqiu              #+#    #+#             */
/*   Updated: 2023/06/26 16:56:51 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Iterates through input string and categorises character sequences
 * into tokens.
 * 
 * Spaces are being skipped.
 * The input is divided into <simple commands> which are separated by
 * pipes '|' and may consist of the strings
 * 
 * 		<infile exe opt1 opt2 opt3 >outfile
 * 
 * Each of these input strings represent a token. These tokens are saved
 * according to each simple command. 
 * 
 * @param data 	Overarching struct to hold all necessarry data.
 * @param input Input string delivered by <readline>.
 * @return t_error 
 */
t_error	ft_lexer(t_data *data, char *input)
{
	int		i;
	bool	exe_found;

	data->token = NULL;
	i = 0;
	while (input[i])
	{
		exe_found = false;
		i += ft_skip_space(input);
		while (input[i] != '|')
		{
			data->err = ft_categorise(data, input + i, &exe_found);
			if (data->err != SUCCESS)
				return (data->err);
			while (input[i] != ' ' && input[i] != '|')
				i++;
			i += ft_skip_space(input + i);
		}
		i++;
	}
	return (SUCCESS);
}


t_error	ft_categorise(t_data *data, char *input, bool *exe_found)
{
	int		i;

	i = 0;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			data->err = ft_save_heredoc(data, input);
		else
			data->err = ft_save_infile(data, input);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			data->err = ft_save_append(data, input);
		else
			data->err = ft_save_outfile(data, input);
	}
	else
		data->err = ft_categorise2(data, input, exe_found);
	if (data->err != SUCCESS)
		return (data->err);
	return (SUCCESS);
}


t_error	ft_categorise2(t_data *data, char *input, bool *exe_found)
{
	if (exe_found == false)
	{
		data->err = ft_save_exe(data, input);
		exe_found = true;
	}
	else
		data->err = ft_save_opt(data, input);
	if (data->err != SUCCESS)
		return (data->err);
	return (SUCCESS);
}


t_error	ft_save_heredoc(t_data *data, char *input)
{
	char	*tmp;

	data->err = ft_extract_str(input, tmp);
}

/* data->err = ft_extract_str(input + i, tmp, &i);
	if (data->err != SUCCESS)
		return (data->err); */