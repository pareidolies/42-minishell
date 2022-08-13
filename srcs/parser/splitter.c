/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:00:41 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 22:41:41 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_taillemot2(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quote((char *)str, i))
			break ;
		i++;
	}
	return (i);
}

static	int	ft_nbrmots2(const char *str, char c)
{
	int	i;
	int	j;
	int	mots;

	mots = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		while (str[i] && str[i] == c && !is_in_quote((char *)str, i))
			i++;
		j = ft_taillemot2(&str[i], c);
		if (j > 0)
			mots++;
		i = i + j;
	}
	return (mots);
}

static	char	*ft_cpymot2(const char *src, int n)
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

char	**ft_boucle2(int tailletab, const char *str, char c, char **res)
{
	int	i;
	int	j;
	int	lenmot;

	i = -1;
	j = 0;
	while (++i < tailletab)
	{
		while (str[j] && str[j] == c && !is_in_quote((char *)str, j))
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

char	**split_parser(const char *str, char c)
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
