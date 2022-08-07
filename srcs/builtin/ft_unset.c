/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:26:24 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/07 22:26:26 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return values OK */

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