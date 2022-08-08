/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:40:39 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 18:40:48 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expansion_start(char *str, char *initial, int pos)
{
	int	i;

	i = 0;
	(void)pos;
	while (str[i])
	{
		if (str[i] == DOLLAR && !is_in_s_quote(initial, pos)
			&& str[i + 1] && (!is_in_d_quote(initial, pos)
				|| ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			&& str[i + 1] != SPACE && str[i + 1] != '=')
			break ;
		i++;
		pos++;
	}
	return (i);
}

int	get_expansion_size(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		return (0);
	if (str[i] == QUESTION)
		return (1);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != DOLLAR && str[i] != S_QUOTE
		&& str[i] != D_QUOTE && str[i] != SPACE
		&& str[i] != ']' && str[i] != '%' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}
