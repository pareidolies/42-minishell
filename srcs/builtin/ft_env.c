/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:28:25 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 12:12:14 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **params, t_env *envlist)
{
	t_env	*var;

	if (nb_param(params) > 1)
	{
		write(2, "env : too many arguments\n", 25);
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
