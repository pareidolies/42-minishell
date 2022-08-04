/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:24:37 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 12:33:58 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_d_quote(char *str, int pos)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == S_QUOTE)
		{
			if (result == 0)
				result = 1;
			else if (result == 1)
				result = 0;
			else if (result == 2)
				result = 2;
		}
		if (str[i] == D_QUOTE)
		{
			if (result == 0)
				result = 2;
			else if (result == 2)
				result = 0;
			else if (result == 1)
				result = 1;
		}
		i++;
	}
	if (result == 2)
		return (2);
	else
		return (0);
}

int	is_in_s_quote(char *str, int pos)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == S_QUOTE)
		{
			if (result == 0)
				result = 1;
			else if (result == 1)
				result = 0;
			else if (result == 2)
				result = 2;
		}
		if (str[i] == D_QUOTE)
		{
			if (result == 0)
				result = 2;
			else if (result == 2)
				result = 0;
			else if (result == 1)
				result = 1;
		}
		i++;
	}
	if (result == 1)
		return (1);
	else
		return (0);
}

int	get_expanded_token_start(char *str, char *initial, int pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && !is_in_s_quote(initial, pos)
			&& str[i + 1] && (!is_in_d_quote(initial, pos)
			|| ft_isalpha(str[i + 1])) && str[i + 1] != SPACE && str[i + 1] != '=')
		break ;
		i++;
	}
	return (i);
}

int	get_expanded_token_size(char *str)
{
	int i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		return (0);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != DOLLAR && str[i] != S_QUOTE
		&& str[i] != D_QUOTE && str[i] != SPACE
		&& str[i] != ']' && str[i] != '%' && str[i] != '=')
	{
		if (str[i] == QUESTION)
		return (1);
		i++;
	}
	return (i);
}

char	*get_expanded_key(char *str, int size, t_env *envlist)
{
	char *key;
	char *res;

	key = ft_substr(str, 0, size);
	magic_malloc(ADD, 0, key);
	res = ft_getenv(key, envlist);
	magic_malloc(FREE, 0, key);
	return(res);
}

char	*create_expanded_token(char *str, t_env *envlist)
{
	char 	*result;
	int	i;
	int	size;
	int	before_dollar;
	char	*tmp;
	char	*substring;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && !is_in_s_quote(str, i)
			&& str[i + 1] && (!is_in_d_quote(str, i)
			|| ft_isalpha(str[i + 1]))
			&& str[i + 1] != SPACE && str[i + 1] != '=')
		break ;
		i++;
	}
	result = ft_substr(str, 0, i);
	magic_malloc(ADD, 0, result);
	while(str[i])
	{
		i++;
		size = get_expanded_token_size(&str[i]);
        //printf("size : %d\n", size);
        /*if (!str[i])
        {
            tmp = ft_strjoin(result, "$");
            magic_malloc(ADD, 0, tmp);
            magic_malloc(FREE, 0, result);
            return (tmp);
        }*/
	if (!str[i])
		break ;
	tmp = ft_strjoin(result, get_expanded_key(&str[i], size, envlist));
	magic_malloc(ADD, 0, tmp);
	magic_malloc(FREE, 0, result);
	//printf("*result* step 2 : %s\n", result);
	i = i + size;
	before_dollar = get_expanded_token_start(&str[i], str, i);
	//printf("before dollar : %d\n", before_dollar);
	substring = ft_substr(&str[i], 0, before_dollar);
	magic_malloc(ADD, 0, substring);
	result = ft_strjoin(tmp, substring);
	magic_malloc(ADD, 0, result);
	magic_malloc(FREE, 0, tmp);
	magic_malloc(FREE, 0, substring);
	//printf("*result* step 3 : %s\n", result);
	i = i + before_dollar;
	}
	return (result);
}

void	expander(t_token *list, t_env *envlist)
{
	t_token	*current;

	current = list;
	while (current != NULL)
	{
        //if (current->to_expand)
		current->expanded_token = create_expanded_token(current->token, envlist);
        //else
        //    current->expanded_token = current->token;
		current = current->next;
	}
}
