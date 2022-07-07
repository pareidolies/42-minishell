/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:44:36 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 17:04:31 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <unistd.h>

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

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_full_free(t_data *pipex, int flag)
{
	free(pipex->limiter);
	free(pipex->fd);
	free(pipex->pid);
	free(pipex);
	if (flag != 0)
		exit(flag);
	return ;
}
