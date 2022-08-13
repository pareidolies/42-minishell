/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:17:11 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 13:03:24 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static int	is_valid_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

static void	echo_print(int i, char **params, int option)
{
	while (params[i + 1] != NULL)
	{
		ft_putstr_fd(params[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (params[i] != NULL)
		ft_putstr_fd(params[i], 1);
	if (option != 1)
		ft_putstr_fd("\n", 1);
}

/*params[0] = nom commande*/
int	ft_echo(char **params)
{
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (nb_param(params) == 1)
		write(1, "\n", 1);
	else if (nb_param(params) == 2 && is_valid_option(params[1]) == 0)
		return (0);
	else
	{
		while (is_valid_option(params[i]) == 0)
		{
			option = 1;
			i++;
			if (params[i] == NULL)
				return (0);
		}
		echo_print(i, params, option);
	}
	return (0);
}
