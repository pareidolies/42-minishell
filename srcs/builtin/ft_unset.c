#include "minishell.h"

int	ft_unset(char **params, t_env *envlist)
{
	int		i;
	int		error;
	t_env	*var;

	i = 1;
	error = 0;
	if (export_checks(params) != 0)
		return (export_checks(params));
	while (params[i] != NULL)
	{
		if (valid_identifier(params[i]) != 0)
		{
			write(2, "unset : Not a valid identifier\n", 31); /*GESTION ERREUR*/
			error = 1;
		}
		else
		{
			var = ft_getenv_var(params[i], envlist);
			if (var != NULL)
				ft_delenv(var, envlist);
		}
		i++;
	}
	return (error);
}

// int	ft_unset(char **params, t_env *envlist)
// {
// 	int		i;
// 	t_env	*var;

// 	if (nb_param(params) < 1)
// 	{
// 		write(2, "export : Too few arguments\n", 27);
// 		return (1); /*GESTION ERREUR*/
// 	}
// 	i = 1;
// 	while (params[i] != NULL)
// 	{
// 		if (params[i][0] == '-')
// 		{
// 			write(2, "unset : Invalid option\n", 23); /*GESTION ERREUR*/
// 			//exit status = 2
// 		}
// 		else if (valid_identifier(params[i]) != 0)
// 			write(2, "unset : Not a valid identifier\n", 31); /*GESTION ERREUR*/
// 		else
// 		{
// 			var = ft_getenv_var(params[i], envlist);
// 			if (var != NULL)
// 				ft_delenv(var, envlist);
// 		}
// 		i++;
// 	}
// 	return (0);
// }