/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:24 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/25 20:48:10 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	*ft_open_pipes(int n)
{
	int	i;
	int	fd[2];
	int	*pipes;

	i = 0;
	pipes = malloc(sizeof(int) * n);
	if (pipes == NULL)
		exit(1);
	while (i < n)
	{
		if (pipe(fd) < 0)
		{
			ft_close_all(pipes, i);
			free(pipes);
			perror("Pipe error ");
			exit(2);
		}
		pipes[i] = fd[0];
		pipes[i + 1] = fd[1];
		i += 2;
	}
	return (pipes);
}
