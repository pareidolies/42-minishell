#include "minishell.h"

extern int	g_exit_status;

int	ft_update_status(t_env *envlist)
{
	char	*newvalue;

	newvalue = ft_itoa(g_exit_status);
	magic_malloc(ADD, 0, newvalue);
	update_env("?", newvalue, envlist);
	return (0);
}

// void	error_msg(char *command, char *token, char *msg)
// {

// }

