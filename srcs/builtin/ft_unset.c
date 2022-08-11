/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:04:51 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/11 19:46:08 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **params, t_env *envlist)
{
	int		i;
	int		error;
	t_env	*var;

	i = 1;
	error = export_checks(params);
	if (error != 0)
		return (error);
	while (params[i] != NULL)
	{
		if (valid_identifier(params[i]) != 0)
		{
			write(2, "unset : Not a valid identifier\n", 31);
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
