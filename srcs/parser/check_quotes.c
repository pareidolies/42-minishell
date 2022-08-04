/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:43:36 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 11:43:38 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	s_quotes_nbr;
	int	d_quotes_nbr;
	int	i;

	s_quotes_nbr = 0;
	d_quotes_nbr = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] && str[i] == S_QUOTE)
		{
			i++;
			s_quotes_nbr++;
			while (i < (int)ft_strlen(str) && str[i] != S_QUOTE)
				i++;
			if (str[i] && str[i] == S_QUOTE)
				s_quotes_nbr++;
		}
		if (str[i] && str[i] == D_QUOTE)
		{
			i++;
			d_quotes_nbr++;
			while (i < (int)ft_strlen(str) && str[i] != D_QUOTE)
				i++;
			if (str[i] && str[i] == D_QUOTE)
				d_quotes_nbr++;
		}
		i++;
	}
	if (s_quotes_nbr % 2 != 0 || d_quotes_nbr % 2 != 0)
		return (print_errors(QUOTES_ERROR));
	return (0);
}
