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

void	calculate_quotes_nbr(char *str, t_quotes_nbr *quotes_nbr)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] && str[i] == S_QUOTE)
		{
			i++;
			quotes_nbr->simple_q++;
			while (i < (int)ft_strlen(str) && str[i] != S_QUOTE)
				i++;
			if (str[i] && str[i] == S_QUOTE)
				quotes_nbr->simple_q++;
		}
		if (str[i] && str[i] == D_QUOTE)
		{
			i++;
			quotes_nbr->double_q++;
			while (i < (int)ft_strlen(str) && str[i] != D_QUOTE)
				i++;
			if (str[i] && str[i] == D_QUOTE)
				quotes_nbr->double_q++;
		}
		i++;
	}
}

int	check_quotes(char *str)
{
	t_quotes_nbr	quotes_nbr;

	quotes_nbr.simple_q = 0;
	quotes_nbr.double_q = 0;
	calculate_quotes_nbr(str, &quotes_nbr);
	if (quotes_nbr.simple_q % 2 != 0 || quotes_nbr.double_q % 2 != 0)
		return (print_errors(QUOTES_ERROR));
	return (0);
}
