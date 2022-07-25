#include "../../includes/minishell.h"
#include "builtin.h"

int	ft_unset(char **params, t_env *envlist)
{
	int		i;
	t_env	*var;

	if (nb_param(params) < 1)
	{
		write(2, "export : Too few arguments\n", 27);
		return (1); /*GESTION ERREUR*/
	}
	i = 1;
	while (params[i] != NULL)
	{
		var = ft_getenv_var(params[i], envlist);
		if (var != NULL)
		{
			ft_delenv(var, envlist);
		}
		i++;
	}
	return (0);
}

void	ft_delenv(t_env *var, t_env *envlist)
{
	t_env	*tmp;

	tmp = envlist;
	while (tmp->next != var)
		tmp = tmp->next;
	tmp->next = var->next;
	free(var->key);
	free(var->value);
	free(var);
}