/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_malloc_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:43:46 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 12:43:49 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_free(t_malloc *node)
{
	if (!node)
		return ;
	if (node->addr)
		free(node->addr);
	node->addr = NULL;
	free(node);
	node = NULL;
}

void	free_all_and_quit(t_malloc *first, int error)
{
	t_malloc	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		ft_free(tmp);
	}
	exit (error);
}

/* Tres important : si l'element n'a pas ete malloc,
current == NULL et donc on sort*/

void	free_one_element(t_malloc **first, void *addr)
{
	t_malloc	*current;

	current = *first;
	while (current && current->addr != addr)
		current = current->next;
	if (current == NULL)
		return ;
	if (current == (*first))
	{
		if (current->next == NULL)
			return (ft_free(current));
		else
		{
			(*first) = current->next;
			current->next->prev = NULL;
		}
	}
	else if (current->next)
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	else if (!current->next)
		current->prev->next = NULL;
	ft_free(current);
}
