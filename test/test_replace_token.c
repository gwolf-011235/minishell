/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_replace_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:51:44 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/31 14:52:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_test_replace_token(void)
{
	char *string1 = ft_strdup("Ein Fuchs springt über den See.");
	char *string2 = ft_strdup("Dies ist Text \\u mit einem Token");
	char *string3 = ft_strdup("Hier müssen \\u zwei Token gefunden \\u werden");
	char *string4 = ft_strdup("\\u: Hier müssen \\t Token gefunden werden \\z");
	char *token = "\\u";
	char *token2 = "\\t";
	char *token3 = "\\z";
	char *replacement = "Gabriel";
	char *replacement2 = "unterschiedliche";
	char *replacement3 = "***WOW***";

	printf("This is before:\t%s\n", string1);
	ft_replace_token(&string1, token, replacement);
	printf("This is after:\t%s\n", string1);
	free(string1);
	printf("This is before:\t%s\n", string2);
	ft_replace_token(&string2, token, replacement);
	printf("This is after:\t%s\n", string2);
	free(string2);
	printf("This is before:\t%s\n", string3);
	ft_replace_token(&string3, token, replacement);
	printf("This is after:\t%s\n", string3);
	free(string3);
	printf("This is before:\t%s\n", string4);
	ft_replace_token(&string4, token, replacement);
	ft_replace_token(&string4, token2, replacement2);
	ft_replace_token(&string4, token3, replacement3);
	printf("This is after:\t%s\n", string4);
	free(string4);
}