/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:09:27 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 13:43:14 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

static int	find_sign(char *str)
{
	int	sign;

	if (str[0] == '+')
		sign = 1;
	else if (str[0] == '-')
		sign = -1;
	else
		sign = 0;
	return (sign);
}

static long long	ft_atoll(char *str)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	sign = find_sign(str);
	if (sign != 0)
		str++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if (i == 18 && ((str[i] > '8')
				|| (sign != -1 && str[i] > '7' && str[i] <= '9')))
		{
			write(2, "exit: numeric argument required\n", 32);
			magic_malloc(2, 0, NULL);
		}
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1)
		return (nb * sign);
	return (nb);
}

static int	is_full_digits(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) != 1 && str[0] != '+' && str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	exit_checks(char **params)
{
	if (nb_param(params) == 1)
		return (0);
	if (is_full_digits(params[1]) == 1 && nb_param(params) > 2)
	{
		write(2, "exit : too many arguments\n", 26);
		return (1);
	}
	if (is_full_digits(params[1]) == 0 || ft_strlen(params[1]) > 20)
	{
		write(2, "exit: numeric argument required\n", 32);
		magic_malloc(2, 0, NULL);
	}
	return (0);
}

int	ft_exit(t_data *mini, char **params, t_env *envlist)
{
	long long	value;
	int			code;

	close(mini->std_in);
	close(mini->std_out);
	if (mini->nb_pid == 1)
		ft_putstr_fd_color("exit\n", 2, ANSI_COLOR_LIGHT_YELLOW);
	ft_update_status(envlist);
	if (exit_checks(params) == 1)
		return (1);
	if (nb_param(params) == 2)
	{
		value = ft_atoll(params[1]);
		code = (value % 256 + 256) % 256;
	}
	else
	{
		code = g_exit_status;
	}
	magic_malloc(code, 0, NULL);
	return (0);
}
