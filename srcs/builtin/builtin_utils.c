#include "minishell.h"
#include <stddef.h>

int	nb_param(char **params)
{
	int	i;

	i = 0;
	while (params[i] != NULL)
	{
		i++;
	}
	return (i);
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