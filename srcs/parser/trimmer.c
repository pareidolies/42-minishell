/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:03:03 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:15:07 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_substring(char *str, int *i, int start, char c, char *tmp)
{
	char	*substring;
	char	*result;

	if (c == S_QUOTE || c == D_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		substring = ft_substr(str, start + 1, *i - start - 1);
		magic_malloc(ADD, 0, substring);
		result = ft_strjoin(tmp, substring);
		magic_malloc(FREE, 0, substring);
		(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != S_QUOTE && str[*i] != D_QUOTE)
				(*i)++;
		substring = ft_substr(str, start, *i - start);
		magic_malloc(ADD, 0, substring);
		result = ft_strjoin(tmp, substring);
		magic_malloc(FREE, 0, substring);
	}
	return (result);
}

char	*withdraw_quotes(char *str)
{
	int		i;
	char	*result;
	int		start;
	char	*tmp;

	tmp = ft_strdup("");
	magic_malloc(ADD, 0, tmp);
	i = 0;
	while (str[i])
	{
		start = i;
		result = get_substring(str, &i, start, str[i], tmp);
		magic_malloc(ADD, 0, result);
		magic_malloc(FREE, 0, tmp);
		tmp = ft_strdup(result);
		magic_malloc(ADD, 0, tmp);
		magic_malloc(FREE, 0, result);
	}
	result = ft_strdup(tmp);
	magic_malloc(FREE, 0, tmp);
	return (result);
}
