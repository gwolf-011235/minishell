#include "minishell_error.h"

/**
 * @brief Print warning messages depending on
 * received indicator and trigger string.
 *
 * @param indic		Indicator string for error message.
 * @param trigger	Trigger string causing the error.
 * @return t_err	ERR_HEREDOC_EOF, ERR_DIR, SUCCESS
 */
t_err	ft_print_warning(char *indic, char *trigger)
{
	if (!ft_strncmp(indic, "heredoc", 8))
	{
		ft_putstr_fd("minishell: warning: here-document at line 42 \
	delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd("')", 2);
		return (ERR_HEREDOC_EOF);
	}
	else if (!ft_strncmp(indic, "dir", 4))
	{
		g_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (ERR_DIR);
	}
	else
		return (ft_print_warning2(indic, trigger));
}

/**
 * @brief Continuation of ft_print_warning()
 *
 * @param indic 	Indicator string for error message.
 * @param trigger 	Trigger string causing the error.
 * @return t_err 	ERR_DIR, SUCCESS
 */
t_err	ft_print_warning2(char *indic, char *trigger)
{
	if (!ft_strncmp(indic, "nodir", 6))
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (ERR_DIR);
	}
	if (!ft_strncmp(indic, "nocmd", 6))
	{
		g_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trigger, 2);
		ft_putendl_fd(": command not found", 2);
		return (SUCCESS);
	}
	return (SUCCESS);
}

t_err	ft_err_stat(const char *pathname, struct stat *statbuf, char *msg)
{
	int	ret;

	errno = 0;
	ret = stat(pathname, statbuf);
	if (ret == -1)
	{
		if (errno == ENOENT)
			return (ERR_NO_DIR);
		else
		{
			perror(msg);
			return (ERR_STAT);
		}
	}
	return (SUCCESS);
}
