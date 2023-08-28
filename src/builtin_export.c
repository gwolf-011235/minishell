/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 08:11:30 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/28 17:35:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin_export.c
 * @brief Implementation of builtin export.
 */
#include "mod_builtin.h"

/**
 * @brief Export a variable into environment.
 *
 * Check arg size with ft_get_array_size().
 * If no arg is given ft_print_env_sorted().
 * Check env keylen of the given string.
 * If legal key insert variable.
 * If legal key and concatenate try to concatenate.
 * If not legal report error.
 * @param argv NULL terminated args.
 * @param env_tab Environment.
 */
void	ft_export(char **argv, t_hashtable *env_tab)
{
	size_t	size;
	t_err	err;
	size_t	i;

	size = 0;
	g_status = 0;
	ft_get_array_size(argv, &size);
	if (size == 1)
		return (ft_print_env_sorted(env_tab));
	i = 1;
	while (argv[i])
	{
		size = 0;
		err = ft_get_env_keylen(argv[i], &size);
		if (err == SUCCESS)
			err = ft_check_and_update_env(argv[i], env_tab, size);
		else if (err == ERR_CONCAT)
			err = ft_concatenate(argv[i], env_tab, size);
		if (err != SUCCESS && err != ERR_INVALID_NAME)
			return (ft_export_error(err, argv[i]));
		else if (err == ERR_INVALID_NAME)
			ft_export_error(err, argv[i]);
		i++;
	}
}

/**
 * @brief Print ASCII sorted environment.
 *
 * Create envp with ft_envp_create().
 * If error print with ft_export_error().
 * Use ft_quicksort_string() to sort envp.
 * Print env_strings with ft_pretty_print_envp().
 * Destroy envp with ft_envp_destroy().
 * @param env_tab Environment.
 */
void	ft_print_env_sorted(t_hashtable *env_tab)
{
	char	**envp;
	t_err	err;

	envp = NULL;
	err = ft_envp_create_all(env_tab, &envp);
	if (err != SUCCESS)
		return (ft_export_error(err, NULL));
	ft_quicksort_strings(envp, 0, env_tab->num_exports - 1);
	err = ft_pretty_print_envp(envp, env_tab->num_exports);
	if (err != SUCCESS)
		return (ft_export_error(err, NULL));
	ft_envp_destroy(&envp);
}

/**
 * @brief Print env_str in pretty from.
 *
 * Print "export ".
 * Print key of the env_var.
 * If followed by a value print equals sign and value enclosed in double quotes.
 * @param envp Array with all env_str.
 * @param size Size of pointer array.
 * @return t_err SUCCESS, ERR_INVALID_NAME.
 */
t_err	ft_pretty_print_envp(char **envp, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	keylen;
	t_err	err;

	i = 0;
	while (i < size)
	{
		keylen = 0;
		err = ft_get_env_keylen(envp[i], &keylen);
		if (err != SUCCESS)
			return (err);
		ft_putstr_fd("export ", 1);
		j = 0;
		while (j < keylen)
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if (envp[i][keylen] == '=')
			ft_printf("=\"%s\"", envp[i] + keylen + 1);
		ft_printf("\n");
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Check env_str for valid key. If so update environment.
 *
 * Check key with ft_get_env_keylen().
 * If valid ft_strdup() the given env_str.
 * Then update environment with ft_update_env_var().
 * @param str Env_str to check.
 * @param env_tab Environment.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_HT_NO_INSERT, ERR_HT_NO_SWAP.
 */
t_err	ft_check_and_update_env(char *str, t_hashtable *env_tab, size_t keylen)
{
	t_err	err;
	char	*tmp;

	tmp = NULL;
	if (ft_err_strdup(str, &tmp, "minishell: malloc") == ERR_MALLOC)
		return (ERR_MALLOC);
	if (tmp[keylen] == '=')
		err = ft_update_env_var(env_tab, tmp, keylen, true);
	else
		err = ft_update_env_var(env_tab, tmp, keylen, false);
	if (err != SUCCESS)
		free(tmp);
	return (err);
}

/**
 * @brief Concatenates string to existing var.
 *
 * Check if var exists, if not insert it. Needs to get rid of '+' in env_str.
 * If the var exists check if it has value.
 * If value ft_strjoin() the existing env_str with the position after the '='
 * If no value take position on the '='.
 * Swap the variable with the new env_str.
 * @param env_str Env string which values should be concatenated.
 * @param env_tab Environment.
 * @param keylen Len of key of env
 * @return t_err SUCCESS, ERR_MALLOC, ERR_HT_NO_SWAP
 */
t_err	ft_concatenate(char *env_str, t_hashtable *env_tab, size_t keylen)
{
	char		*concat;
	t_env_var	*env_var;
	t_err		err;

	env_var = ft_hashtable_lookup(env_tab, env_str, keylen);
	if (!env_var)
	{
		ft_eat_char2(env_str, keylen);
		return (ft_check_and_update_env(env_str, env_tab, keylen));
	}
	concat = NULL;
	if (env_var->has_value)
		err = ft_err_strjoin(env_var->env_string, ft_strchr(env_str, '=') + 1,
				&concat, "minishell: malloc");
	else
		err = ft_err_strjoin(env_var->env_string, ft_strchr(env_str, '='),
				&concat, "minishell: malloc");
	if (err != SUCCESS)
		return (err);
	err = ft_hashtable_swap(env_tab, concat, keylen, true);
	if (err != SUCCESS)
		free(concat);
	return (err);
}
