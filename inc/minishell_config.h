/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_config.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:46:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/28 18:13:51 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONFIG_H
# define MINISHELL_CONFIG_H

/* ====== BASE SETTINGS ====== */

# define HASHTABLE_SIZE 10
# define MAX_SHLVL 10
# define BUF_SIZE 2048

/* ====== PROMPT ====== */

# define PS1 "PS1=\\u@\\h mini🐚 $ "
# define PS2 "PS2=tell me more 🤌 > "
# define PS1_STD "$ "
# define PS2_STD "> "
# define UNKNOWN "UNKNOWN"

#endif