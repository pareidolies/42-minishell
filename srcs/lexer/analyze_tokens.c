/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:29:36 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 18:29:56 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analyze_tokens_type(t_token *list)
{
	t_token	*current;
	int		len;

	current = list;
	if (!current)
		return (1);
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
	return (0);
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
