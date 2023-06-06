/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_replace_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:51:44 by gwolf             #+#    #+#             */
/*   Updated: 2023/06/06 13:18:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_replace_token(void)
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
	//empty replcament string
	{
		char *string = ft_strdup("If want to lose the backslash: \\END");
		char *token = "\\";
		char *replacement = "";

		printf("This is before:\t%s\n", string);
		ft_replace_token(&string, token, replacement);
		printf("This is after:\t%s\n", string);
		free(string);
	}
}