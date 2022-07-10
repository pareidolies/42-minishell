/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:15 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 23:32:44 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int	primary_checks(int argc, char **envp)
{
	if (argc <= 5)
	{
		write(2, "Syntax error. Too few arguments.\n", 33);
		exit(1);
	}
	if (envp[0] == NULL)
	{
		write(2, "No environment variable.\n", 25);
		exit(2);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*pipex;
	int		status;
	int		i;

	i = -1;
	primary_checks(argc, envp);
	pipex = ft_init(argc, argv);
	pipex->fd = ft_open_pipes(pipex->nbfd);
	pipex->pid[0] = ft_fork_f(argv, envp, pipex);
	while (pipex->index < pipex->nbpid - 1)
	{
		pipex->pid[pipex->index] = ft_fork(argv, envp, pipex);
		pipex->index++;
	}
	pipex->pid[pipex->index] = ft_fork_l(argv, envp, pipex);
	ft_close_all(pipex->fd, pipex->nbfd);
	while (++i < pipex->nbpid - 1)
		wait(&status);
	waitpid(pipex->pid[pipex->nbpid - 1], &status, 0);
	unlink("/tmp/pipextmp");
	ft_full_free(pipex, 0);
	return (0);
}

t_data	*ft_init(int argc, char **argv)
{
	t_data	*pipex;

	pipex = ft_calloc(1, sizeof(t_data));
	if (pipex == NULL)
		exit(1);
	if (ft_strncmp(argv[1], "here_doc", 20) == 0)
	{
		pipex->here = 1;
		pipex->limiter = ft_strjoin(argv[2], "\n");
		if (pipex->limiter == NULL)
			ft_full_free(pipex, 2);
		ft_heredoc(pipex->limiter, pipex);
	}
	else
		pipex->here = 0;
	pipex->nbfd = (argc - 4 - pipex->here) * 2;
	pipex->nbpid = argc - 3 - pipex->here;
	pipex->pid = malloc(sizeof(int) * pipex->nbpid);
	if (pipex->pid == NULL)
	{
		ft_full_free(pipex, 3);
	}
	return (pipex);
}
