/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:34:25 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:56:58 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	magic_malloc(FREE, 0, var->key);
	magic_malloc(FREE, 0, var->value);
	magic_malloc(FREE, 0, var);
}

int	update_env(char *key, char *newvalue, t_env	*envlist)
{
	t_env	*var;

	var = ft_getenv_var(key, envlist);
	if (var == NULL)
	{
		var = ft_new_var_split(key, newvalue);
		if (var == NULL)
			return (perror("update_env (ft_new_var_split) "), 1);
		ft_lstaddback(&envlist, var);
	}
	else
	{
		if (newvalue != NULL)
		{
			magic_malloc(FREE, 0, var->value);
			var->value = ft_strdup(newvalue);
			magic_malloc(ADD, 0, var->value);
		}
	}
	return (0);
}

t_env	*ft_new_var_split(char *key, char *value)
{
	t_env	*var;

	var = magic_malloc(MALLOC, sizeof(t_env), NULL);
	var->key = ft_strdup(key);
	magic_malloc(ADD, 0, var->key);
	if (value != NULL)
	{
		var->value = ft_strdup(value);
		magic_malloc(ADD, 0, var->value);
	}
	else
		var->value = NULL;
	var->next = NULL;
	return (var);
}
