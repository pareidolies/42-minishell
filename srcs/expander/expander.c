/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:24:37 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:10:08 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_before_dollar_part(int before_dollar, char *tmp, char *str)
{
	char	*result;
	char	*substring;

	substring = ft_substr(str, 0, before_dollar);
	magic_malloc(ADD, 0, substring);
	result = ft_strjoin(tmp, substring);
	magic_malloc(ADD, 0, result);
	magic_malloc(FREE, 0, tmp);
	magic_malloc(FREE, 0, substring);
	return (result);
}

char	*get_expanded_key(char *str, int size, t_env *envlist)
{
	char	*key;
	char	*res;

	key = ft_substr(str, 0, size);
	magic_malloc(ADD, 0, key);
	res = ft_getenv(key, envlist);
	printf("key : %s\n", res);
	magic_malloc(FREE, 0, key);
	return (res);
}

char	*add_key_part(char *result, char *str, int size, t_env *envlist)
{
	char	*tmp;

	tmp = ft_strjoin(result, get_expanded_key(str, size, envlist));
	magic_malloc(ADD, 0, tmp);
	magic_malloc(FREE, 0, result);
	return (tmp);
}

char	*create_expanded_token(char *str, t_env *envlist)
{
	char	*result;
	int		i;
	int		size;
	int		before_dollar;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	magic_malloc(ADD, 0, tmp);
	while (str[i])
	{
		before_dollar = get_expansion_start(&str[i], str, i);
		result = add_before_dollar_part(before_dollar, tmp, &str[i]);
		i = i + before_dollar + 1;
		if (i > (int)ft_strlen(str))
			return (result);
		size = get_expansion_size(&str[i]);
		tmp = add_key_part(result, &str[i], size, envlist);
		i = i + size;
	}
	return (tmp);
}

void	expander(t_token *list, t_env *envlist)
{
	t_token	*current;

	current = list;
	while (current != NULL)
	{
		current->expanded_token = create_expanded_token(current->token, \
		envlist);
		current = current->next;
	}
}
