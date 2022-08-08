/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:37:16 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 18:37:25 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_result(int result, char c)
{
	if (c == S_QUOTE)
	{
		if (result == 0)
			return (1);
		else if (result == 1)
			return (0);
		else if (result == 2)
			return (2);
	}
	if (c == D_QUOTE)
	{
		if (result == 0)
			return (2);
		else if (result == 2)
			return (0);
		else if (result == 1)
			return (1);
	}
	return (result);
}

int	is_in_quote(char *str, int pos)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			result = calculate_result(result, str[i]);
		i++;
	}
	return (result);
}

int	is_in_d_quote(char *str, int pos)
{
	int	result;

	result = is_in_quote(str, pos);
	if (result == 2)
		return (2);
	else
		return (0);
}

int	is_in_s_quote(char *str, int pos)
{
	int	result;

	result = is_in_quote(str, pos);
	if (result == 1)
		return (1);
	else
		return (0);
}
