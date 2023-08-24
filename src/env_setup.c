/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:51:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/24 12:47:41 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env_setup.c
 * @brief Import environment and set specific variables if missing.
 */

#include "mod_env.h"

/**
 * @brief Impot environment and sets some specific vars.
 *
 * ft_import_environ() to fill env_table.
 * Check for missing PWD, SHLVL, PS1, PS2.
 * Insert if necessary.
 * Increment SHLVL.
 * Set special parameter $$ and $0.
 * @param env_table Environment.
 * @param argv_zero First argument of argv.
 * @param buf Pointer to buffer
 */
void	ft_env_setup(t_hashtable *env_table, char *argv_zero, t_buf *buf)
{
	ft_import_environ(env_table);
	ft_check_missing_env(env_table, buf);
	ft_set_special_params(env_table, argv_zero);
}

/**
 * @brief Import env_vars from global environ.
 *
 * If environ is null do nothing.
 * Loop through the environ array. Environ is NULL-terminated.
 * Copy the string into environment with ft_copy_envion_str().
 * If ERR_HT_NO_INSERT continue looping. This ensures, that there
 * are no duplicates in environment.
 * If ERR_INVALID_NAME break out of loop (corrupted environ?)
 * If ERR_MALLOC break out of loop - no memory to continue.
 * Handles all errors.
 * @param env_table Environment.
 */
void	ft_import_environ(t_hashtable *env_table)
{
	int		i;
	t_err	err;

	i = 0;
	if (environ[i] == NULL)
		return ;
	while (environ[i] != NULL)
	{
		err = ft_copy_environ_str(env_table, environ[i]);
		if (err != SUCCESS && err != ERR_HT_NO_INSERT)
			break ;
		i++;
	}
	if (err == ERR_INVALID_NAME)
		ft_putendl_fd("minishell: warning: possible corrupted environ", 2);
	else if (err == ERR_MALLOC)
		ft_putendl_fd("minishell: warning: error while parsing environ", 2);
}

/**
 * @brief Copies a single string from environ into hashtable.
 *
 * Check if valid env_key with ft_get_env_keylen().
 * If yes generate copy with ft_strdup().
 * If str on pos keylen is an equals sign, the var has a value (standard case).
 * If no equals it has no value, and will not be inserted.
 * If insertion fails free str.
 * @param env_table Environment.
 * @param environ_str Single str from environ.
 * @return t_err SUCCESS, ERR_INVALID_NAME, ERR_MALLOC,
 * ERR_HT_NO_INSERT, ERR_EMPTY
 */
t_err	ft_copy_environ_str(t_hashtable *env_table, char *environ_str)
{
	char	*env_str;
	size_t	keylen;
	t_err	err;

	keylen = 0;
	if (ft_get_env_keylen(environ_str, &keylen) == ERR_INVALID_NAME)
		return (ERR_INVALID_NAME);
	env_str = NULL;
	if (ft_err_strdup(environ_str, &env_str,
			"minishell: startup") == ERR_MALLOC)
		return (ERR_MALLOC);
	if (env_str[keylen] == '=')
	{
		errno = 0;
		err = ft_hashtable_insert_export(env_table, env_str, keylen, true);
		if (err == ERR_MALLOC)
			perror("minishell: startup");
		if (err == ERR_MALLOC || err == ERR_HT_NO_INSERT)
			free(env_str);
		return (err);
	}
	else
		free(env_str);
	return (SUCCESS);
}

/**
 * @brief Checks env variables PWD, SHLVL, PS1, PS2.
 *
 * If PWD not found create and insert it.
 * If SHLVL not found create and insert it.
 * If SHLVL found increment it.
 * If PS1 and/or PS2 not found create and insert it.
 * Handles all errors.
 * @param env_table Environment.
 * @param buf Buffer.
 */
void	ft_check_missing_env(t_hashtable *env_table, t_buf *buf)
{
	if (ft_hashtable_lookup(env_table, "PWD", 3) == NULL)
	{
		if (ft_insert_env_pwd(env_table, buf) != SUCCESS)
			ft_putendl_fd("minishell: warning: PWD not created", 2);
	}
	if (ft_hashtable_lookup(env_table, "SHLVL", 5) == NULL)
	{
		if (ft_insert_env_shlvl(env_table) != SUCCESS)
			ft_putendl_fd("minishell: warning: SHLVL not created", 2);
	}
	else
	{
		if (ft_increment_shlvl(env_table) != SUCCESS)
			ft_putendl_fd("minishell: warning: SHLVL not updated", 2);
	}
	if (ft_hashtable_lookup(env_table, "PS1", 3) == NULL)
	{
		if (ft_insert_env_prompt(env_table, PS1) != SUCCESS)
			ft_putendl_fd("minishell: warning: PS1 not created", 2);
	}
	if (ft_hashtable_lookup(env_table, "PS2", 3) == NULL)
	{
		if (ft_insert_env_prompt(env_table, PS2) != SUCCESS)
			ft_putendl_fd("minishell: warning: PS2 not created", 2);
	}
}

/**
 * @brief Copies and inserts prompt string.
 *
 * @param env_table Environment
 * @param prompt Prompt string to be copied.
 * @return t_err SUCCESS, ERR_MALLOC, ERR_HT_NO_INSERT
 */
t_err	ft_insert_env_prompt(t_hashtable *env_table, char *prompt)
{
	char	*env_prompt;
	t_err	err;

	env_prompt = NULL;
	if (ft_err_strdup(prompt, &env_prompt, "minishell: startup") == ERR_MALLOC)
		return (ERR_MALLOC);
	errno = 0;
	err = ft_hashtable_insert(env_table, env_prompt, 3, true);
	if (err == ERR_MALLOC)
		perror("minishell: startup");
	if (err == ERR_MALLOC || err == ERR_HT_NO_INSERT)
		free(env_prompt);
	return (err);
}
