/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:28:04 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 22:56:14 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_reads	save;
	t_reads			*first;
	int				count;
	char			*str;

	if (fd < 0 || 20 <= 0)
		return (NULL);
	first = &save;
	first->count = 1;
	count = ft_read(fd, first, first);
	str = ft_extract(first, count);
	if (count == 0 || str == NULL || str[0] == '\0')
	{
		ft_clean(first, count, 1);
		return (NULL);
	}
	else
		ft_clean(first, count, 0);
	return (str);
}

int	ft_read(int fd, t_reads *head, t_reads *node)
{
	char	*buffer;
	int		nread;
	int		count;

	buffer = malloc(sizeof(char) * 20);
	if (buffer == NULL)
		return (0);
	nread = 1;
	while (nread != 0 && ft_find_eol(node) == 0)
	{
		nread = read(fd, buffer, 20);
		if (nread == 0)
			node = ft_lastnode(head, node);
		if (nread == -1 || (node == head && nread == 0))
		{
			return (free(buffer), 0);
		}
		if (nread > 0)
			node = ft_addnew_back(head, node, buffer, nread);
		if (node == NULL)
			return (free(buffer), 0);
	}
	count = node->count;
	return (free(buffer), count);
}

t_reads	*ft_lastnode(t_reads *head, t_reads *node)
{
	t_reads	*last;

	last = NULL;
	if (node->content == NULL)
		last = node;
	else
	{
		last = malloc(sizeof(t_reads));
		if (last == NULL)
		{
			ft_clean(head, node->count, 1);
			return (NULL);
		}
		node->next = last;
		last->count = node->count + 1;
	}
	last->content = NULL;
	last->nb_read = 0;
	last->next = NULL;
	last->iter = 0;
	return (last);
}

t_reads	*ft_addnew_back(t_reads *head, t_reads *curr, char *buffer, int nread)
{
	t_reads	*new;
	int		i;

	i = -1;
	if (curr->content == NULL)
		new = curr;
	else
	{
		new = malloc(sizeof(t_reads));
		if (new == NULL)
			return (ft_clean(head, curr->count, 1), NULL);
		curr->next = new;
		new->count = curr->count + 1;
	}	
	if (nread > 0)
		new->content = malloc(nread * sizeof(char));
	if (new->content == NULL)
		return (ft_clean(head, curr->count, 1), NULL);
	while (++i < nread)
		new->content[i] = buffer[i];
	new->nb_read = nread;
	new->iter = 0;
	new->next = NULL;
	return (new);
}

int	ft_find_eol(t_reads *node)
{
	int	i;
	int	nb_eol;

	i = 0;
	nb_eol = 0;
	while (i < node->nb_read)
	{
		if (node->content[i] == '\n')
		{
			nb_eol++;
			if (nb_eol > node->iter && node->count == 1)
				return (nb_eol);
		}
		i++;
	}
	if (nb_eol <= node->iter)
		return (0);
	else
		return (nb_eol);
}
