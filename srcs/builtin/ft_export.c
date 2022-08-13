/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:08:49 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 13:05:49 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In manual : "When no arguments are given, the results are unspecified." */
/*We then choose to treat this case as a syntax error. */
int	ft_export(char **params, t_env *envlist)
{
	int		i;
	char	*eq_position;
	int		error;

	i = 1;
	error = export_checks(params);
	if (error != 0)
		return (error);
	while (params[i] != NULL)
	{
		eq_position = ft_strchr(params[i], '=');
		if (eq_position == NULL)
		{
			error = valid_identifier(params[i]);
			if (error == 1)
				write(2, "export : Not a valid identifier\n", 32);
			else if (error == 0 && ft_getenv_var(params[i], envlist) == NULL)
				update_env(params[i], NULL, envlist);
		}
		else
			error = export_value(params[i], eq_position, envlist);
		i++;
	}
	return (error);
}

int	export_checks(char **params)
{
	if (nb_param(params) < 2)
	{
		write(2, "export/unset : Too few arguments\n", 33);
		return (1);
	}
	if (params[1][0] == '-')
	{
		write(2, "export/unset : Invalid option\n", 30);
		return (2);
	}
	return (0);
}

int	export_value(char *str, char *equal, t_env *envlist)
{
	char	*key;
	int		error;

	error = 0;
	key = export_find_name(str);
	if (valid_identifier(key) == 0 && equal[1] == '\0')
		update_env(key, "", envlist);
	else if (valid_identifier(key) == 0)
		update_env(key, equal + 1, envlist);
	else
	{
		write(2, "export : Not a valid identifier\n", 32);
		error = 1;
	}
	magic_malloc(FREE, 0, key);
	return (error);
}

char	*export_find_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	magic_malloc(ADD, 0, name);
	return (name);
}

/*Variable name must be only composed of letters, underscores and digits*/
/*Digits NEVER in starting position, No special character included*/
int	valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (name[0] >= '0' && name[0] <= '9')
		return (1);
	if (name[0] == '\0')
		return (1);
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
