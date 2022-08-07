/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:26:48 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/07 22:26:51 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str)
{
	int	i;
	int	minus;
	long long	nb;

	i = 0;
	minus = 0;
	nb = 0;
	while ((str[i] == ' ' | str[i] == '\t' | str[i] == '\n' | str[i] == '\v'
			| str[i] == '\f' | str[i] == '\r') && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if ((minus % 2) == 1)
		nb = nb * (-1);
	return (nb);
}

int ft_exit(char **params, t_env *envlist)
{
	long long	value;
	int			code;
	int			i;

	if (nb_param(params) > 2)
	{
		write(2, "exit : Too many arguments\n", 26);
		return (1);
	}
	if (nb_param(params) == 2)
	{
		i = 0;
		while (params[1][i])
		{
			if (!ft_isdigit(params[1][i]))
			{
				write(2, "exit: numeric argument required\n", 32);
				magic_malloc(2, 0, NULL);
			}
			i++;
		}	
		value = ft_atoll(params[1]);
		//printf("%lld\n", value);
		if (value > 255)
			write(2, "exit: numeric argument required2\n", 32);
		code = value % 256;
	}
	else
	{
		code = ft_atoi(ft_getenv("?", envlist));
	}
	printf("exit\n");
	magic_malloc(code, 0, NULL);
	return (0);
}
