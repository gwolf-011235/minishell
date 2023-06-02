/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:15:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/02 07:50:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test_replace_token(void)
{
	//no token
	{
		char *string = ft_strdup("Ein Fuchs springt über den See.");
		char *token = "\\u";
		char *replacement = "gwolf";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		printf("This is after:\t%s\n", string);
		free(string);
	}
	//one token
	{
		char *string = ft_strdup("Dies ist Text \\u mit einem Token");
		char *token = "\\u";
		char *replacement = "gwolf";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		printf("This is after:\t%s\n", string);
		free(string);
	}
	//two token
	{
		char *string = ft_strdup("Hier müssen \\u zwei Token gefunden \\u werden");
		char *token = "\\u";
		char *replacement = "gwolf";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		printf("This is after:\t%s\n", string);
		free(string);

	}
	//different tokens
	{
		char *string = ft_strdup("\\u: Hier müssen \\t Token gefunden werden \\z");
		char *token = "\\u";
		char *token2 = "\\t";
		char *token3 = "\\z";
		char *replacement = "gwolf";
		char *replacement2 = "unterschiedliche";
		char *replacement3 = "***WOW***";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		ft_replace_token(&string, token2, replacement2);
		ft_replace_token(&string, token3, replacement3);
		printf("This is after:\t%s\n", string);
		free(string);
	}
	//what if token is bigger than replacement
	{
		char *string = ft_strdup("There is a loooong boi in the room.");
		char *token = "loooong boi";
		char *replacement = "short man";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		printf("This is after:\t%s\n", string);
		free(string);
	}

}

int	main(int argc, char **argv)
{
	t_error	err;
	char 	*input;

	while (1)
	{
		err = ft_create_prompt(sym_tab, &prompt1, "PS1", PS1_STD);
		if (err != SUCCESS)
			//handle error
		err = ft_create_prompt(sym_tab, &prompt2, "PS2", PS2_STD);
		if (err != SUCCESS)
			//handle error
		input = readline(prompt1);
		if (!input)
			//handle no input e.g. break?
		add_history(input);
		//do stuff
		free(input);
		free(prompt1);
		free(prompt2);
	}
}