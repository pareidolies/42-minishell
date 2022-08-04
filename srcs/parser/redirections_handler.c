/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:58:36 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 12:59:30 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*create_redirection(t_token *list)
{
	t_redirection	*result;
	t_token		*current;
	char		*tmp;

	result = magic_malloc(MALLOC, sizeof(t_redirection), NULL);
	current = list;
	result->prev = NULL;
	result->next = NULL;
	if (current->type == T_INPUT)
		result->mode = INFILE;
	else if (current->type == T_OUTPUT)
		result->mode = TRUNC;
	else if (current->type == T_DELIMITER)
		result->mode = DELIMITER;
	else if (current->type == T_APPEND)
		result->mode = APPEND;
	tmp = ft_strdup(current->expanded_token);
	magic_malloc(ADD, 0, tmp);
	result->str = withdraw_quotes(tmp);
	magic_malloc(ADD, 0, result->str);
	magic_malloc(FREE, 0, tmp);
	result->fd = -1;
	return (result);
}

void	add_redirection(t_token *list, t_redirection *first)
{
	t_redirection	*current;
	t_redirection	*new;

	current = first;
	new = create_redirection(list);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}
