/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:44:16 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 11:57:43 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		if (current->type == T_PIPE && !current->next)
			return (print_errors(TOKENS_ERROR));
		if (current->type == T_PIPE && current->next->type == T_PIPE)
			return (print_errors(TOKENS_ERROR));
		if ((current->type == T_LESS || current->type == T_D_LESS
				|| current->type == T_GREATER || current->type == T_D_GREATER)
			&& !current->next)
			return (print_errors(TOKENS_ERROR));
		if ((current->type == T_LESS || current->type == T_D_LESS
				|| current->type == T_GREATER || current->type == T_D_GREATER)
			&& current->next->type == T_PIPE)
			return (print_errors(TOKENS_ERROR));
		if ((current->type == T_LESS || current->type == T_D_LESS
				|| current->type == T_GREATER || current->type == T_D_GREATER)
			&& (current->next->type == T_LESS
				|| current->next->type == T_D_LESS
				|| current->next->type == T_GREATER
				|| current->next->type == T_D_GREATER))
			return (print_errors(TOKENS_ERROR));
		current = current->next;
	}
	return (0);
}
