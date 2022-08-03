#include "minishell.h"

int	ft_update_status(int code, t_env *envlist)
{
	char	*newvalue;

	if (code == g_exit_status)
		return (0);
	newvalue = ft_itoa(code);
	magic_malloc(ADD, 0, newvalue);
	// if (newvalue == NULL)
	// {
	// 	perror("ft_update_status "); /*GESTION ERREUR MALLOC*/
	// 	return (1);
	// }
	update_env("?", newvalue, envlist);
	g_exit_status = code;
	return (0);
}

// void	error_msg(char *command, char *token, char *msg)
// {

// }

