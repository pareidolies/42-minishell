/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:55:46 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:10:58 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_malloc	*add_one_malloc_element(t_malloc **first, t_malloc *new)
{
	t_malloc	*head;

	head = *first;
	if (!*first)
	{
		(*first) = new;
		(*first)->next = NULL;
		(*first)->prev = NULL;
		return (new);
	}
	else
	{
		while ((*first)->next)
			*first = (*first)->next;
		(*first)->next = new;
		new->next = NULL;
		new->prev = (*first);
		return (head);
	}
}

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

void	*magic_malloc(int choice, size_t size, void *addr)
{
	static t_malloc	*first;
	t_malloc		*node;

	if (choice == FREE)
		free_one_element(&first, addr);
	else if (choice >= 0 && choice <= 255)
		free_all_and_quit(first, choice);
	else if (choice == MALLOC || choice == ADD)
	{
		node = malloc(sizeof(*node));
		if (!node)
			free_all_and_quit(first, MALLOC_ERROR);
		if (choice == MALLOC)
		{
			node->addr = malloc(size);
			if (!node->addr)
				free_all_and_quit(first, MALLOC_ERROR);
		}
		if (choice == ADD)
		{
			if (!addr)
				free_all_and_quit(first, MALLOC_ERROR);
			node->addr = addr;
		}
		first = add_one_malloc_element(&first, node);
		return (node->addr);
	}
	return (NULL);
}

/*main pour tester magic malloc sur des cas simples*/

/*int main()
{
	char *str;
	char *str2;
	char *str3;
	int	i;

	i = 0;
	str = magic_malloc(MALLOC, sizeof(char) * 6, NULL);
	str2 = magic_malloc(MALLOC, sizeof(char) * 6, NULL);
	while (i < 5)
	{
		str[i] = 'a';
		i++;
	}
	while (i < 5)
	{
		str2[i] = 'a';
		i++;
	}
	str3 = malloc(sizeof(char) * 6);
	magic_malloc(ADD, 0, str3);
	while (i < 5)
	{
		str3[i] = 'a';
		i++;
	}
	magic_malloc(QUIT, 0, NULL);
}*/