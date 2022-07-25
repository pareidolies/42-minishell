#include "../../includes/minishell.h"
#include "builtin.h"

int ft_env(char **params, t_env *envlist)
{
	t_env   *var;

	if (nb_param(params) > 1)
	{
		write(2, "env : too many arguments\n", 25);/*GESTION ERREUR*/
		return (1);
	}
	var = envlist;
	while (var != NULL)
	{
		if (var->value != NULL && var->key[0] != '?')
			printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (0);
}