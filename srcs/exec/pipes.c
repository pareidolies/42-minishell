/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:02 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/10 12:04:46 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*open_pipes(t_data *mini)
{
	int	nb_fd;
	int	i;
	int	*fd_tab;
	int	pip[2];

	nb_fd = mini->nb_fd_pipes;
	fd_tab = magic_malloc(MALLOC, sizeof(int) * nb_fd, NULL);
	i = 0;
	while (i < nb_fd)
	{
		if (pipe(pip) < 0)
		{
			ft_close_all(fd_tab, i);
			free(fd_tab);
			print_errors(PIPE_ERROR);
			return (perror(""), NULL);
		}
		fd_tab[i] = pip[0];
		fd_tab[i + 1] = pip[1];
		i += 2;
	}
	return (fd_tab);
}

int	ft_close_all(int *fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(fd[i]);
		i++;
	}
	return (0);
}
