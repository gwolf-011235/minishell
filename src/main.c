/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 14:55:07 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief Main entry point.
 */

#include "minishell.h"
#include "mod_lexer.h"
/* #include "lexer_list.h"
#include "lexer_tok_utils.h" */

#ifdef TESTING
# define main not_main
#endif

int	main(int argc, char **argv)
{
	t_data		*data;
	char 		*input;
	t_tkn_list	*lst;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_failure(data, ERR_MALLOC);
	lst = NULL;
	if (ft_env_setup(data) != SUCCESS)
		printf("NO\n");
	ft_hashtable_insert(data->env_table, "PS1=\\u@\\h:\\w$ ", 3);
	while (1)
	{
		data->err = ft_prompt_create(data->env_table, &data->prompt1, "PS1", PS1_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		data->err = ft_prompt_create(data->env_table, &data->prompt2, "PS2", PS2_STD);
		if (data->err != SUCCESS)
			ft_exit_failure(data, data->err);
		input = readline(data->prompt1);
		if (!input)
			break ;
		add_history(input);
		ft_lex_input(lst, input);
		//do stuff
		free(input);
		free(data->prompt1);
		free(data->prompt2);
	}
	return (0);
}

