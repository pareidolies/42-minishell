/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:00:41 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:01:29 by smostefa         ###   ########.fr       */
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

static	int	ft_taillemot2(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quote(str, i))
			break ;
		i++;
	}
	return (i);
}

static	int	ft_nbrmots2(char *str, char c)
{
	int	i;
	int	j;
	int	mots;

	mots = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && !is_in_quote(str, i))
			str++;
		j = ft_taillemot2(&str[i], c);
		if (j > 0)
			mots++;
		i = i + j;
	}
	return (mots);
}

static	char	*ft_cpymot2(char *src, int n)
{
	char	*dest;

	dest = malloc((n + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

char	**ft_boucle2(int tailletab, char *str, char c, char **res)
{
	int	i;
	int	j;
	int	lenmot;

	i = -1;
	j = 0;
	while (++i < tailletab)
	{
		while (str[j] && str[j] == c && !is_in_quote(str, j))
			j++;
		lenmot = ft_taillemot2(&str[j], c);
		res[i] = ft_cpymot2(&str[j], lenmot);
		if (!res[i])
		{
			i = i - 1;
			while (i >= 0)
			{
				free(res[i]);
				i--;
			}
			return (NULL);
		}
		j = j + lenmot;
	}
	return (res);
}

char	**split_parser(char *str, char c)
{
	char	**res;
	int		tailletab;

	if (!str)
		return (NULL);
	tailletab = ft_nbrmots2(str, c);
	res = malloc((tailletab + 1) * sizeof(char *));
	if (!(res))
		return (NULL);
	res = ft_boucle2(tailletab, str, c, res);
	res[tailletab] = 0;
	return (res);
}

/*
#include <stdio.h>
int main()
{
char **str = ft_split("", ' ');
int i = 0;

while (i < 1)
{
printf("%s\n", str[i]);
i++;
}
}
*/
