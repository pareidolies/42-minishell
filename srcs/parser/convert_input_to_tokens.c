/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_input_to_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:13:31 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:08:14 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_or_redir_or_quote(char c)
{
	if ((c == SPACE) || (c == PIPE)
		|| (c == GREATER) || (c == LESS)
		|| (c == S_QUOTE) || (c == D_QUOTE))
		return (1);
	return (0);
}

int	is_d_redir(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == LESS && str[i + 1] == LESS)
				|| (str[i] == GREATER
					&& str[i + 1] == GREATER))
		return (1);
	return (0);
}

int	is_s_redir(char c)
{
	if (c == LESS || c == GREATER)
		return (1);
	return (0);
}

int	go_before_next_redir_or_pipe_quote_case(int i, char *str, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i + 1] && str[i + 1] != LESS
		&& str[i + 1] != GREATER && str[i + 1] != PIPE)
		return (i + 1 + get_token_size(&str[i + 1]));
	else
		return (i + 1);
}

int	go_before_next_redir_or_pipe(int i, char *str)
{
	while (str[i] && !is_pipe_or_redir_or_quote(str[i]))
		i++;
	if (str[i] && (str[i] == S_QUOTE || str[i] == D_QUOTE))
		return (i + get_token_size(&str[i]));
	else
		return (i);
}

int	get_token_size(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		if (str[i] == PIPE)
			return (1);
		if (str[i + 1])
		{
			if (is_d_redir(&str[i]))
				return (2);
		}
		if (is_s_redir(str[i]))
			return (1);
		if (str[i] == S_QUOTE)
			return (go_before_next_redir_or_pipe_quote_case(i, str, S_QUOTE));
		if (str[i] == D_QUOTE)
			return (go_before_next_redir_or_pipe_quote_case(i, str, D_QUOTE));
		else
			return (go_before_next_redir_or_pipe(i, str));
	}
	return (0);
}

t_token	*convert_input_to_tokens(char *str)
{
	t_token	*list;
	int		i;
	int		size;

	if (!str)
		return (NULL);
	list = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		size = get_token_size(&str[i]);
		if (size == 0)
			break ;
		if (!list)
			list = create_token(&str[i], size);
		else
			add_token(list, &str[i], size);
		i += size;
	}
	return (list);
}

void	analyze_tokens_type(t_token *list)
{
	t_token	*current;
	int		len;

	current = list;
	len = ft_strlen(current->token);
	while (current != NULL)
	{
		if (ft_strncmp(current->token, STR_LESS, len) == 0)
			current->type = T_LESS;
		else if (ft_strncmp(current->token, STR_D_LESS, len) == 0)
			current->type = T_D_LESS;
		else if (ft_strncmp(current->token, STR_GREATER, len) == 0)
			current->type = T_GREATER;
		else if (ft_strncmp(current->token, STR_D_GREATER, len) == 0)
			current->type = T_D_GREATER;
		else if (ft_strncmp(current->token, STR_PIPE, len) == 0)
			current->type = T_PIPE;
		else
			current->type = T_LITERAL;
		current = current->next;
	}
}

void	analyze_literals_type(t_token *list)
{
	t_token	*current;

	current = list;
	while (current->next != NULL)
	{
		if (current->type == T_LESS && current->next->type == T_LITERAL)
			current->next->type = T_INPUT;
		else if (current->type == T_D_LESS)
			current->next->type = T_DELIMITER;
		else if (current->type == T_GREATER)
			current->next->type = T_OUTPUT;
		else if (current->type == T_D_GREATER)
			current->next->type = T_APPEND;
		current = current->next;
	}
}
