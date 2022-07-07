/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:28:49 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 17:12:31 by lmurtin          ###   ########.fr       */
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

int	ft_fork_f(char **argv, char **envp, t_data *pipex)
{
	int	pid;
	int	error;

	pid = fork();
	if (pid < 0)
		return (perror("Fork "), 2);
	pipex->index = 1;
	if (pid == 0)
	{
		if (pipex->here == 1)
			error = ft_child_first2(argv, envp, pipex);
		else
			error = ft_child_first(argv, envp, pipex);
		if (error == 1)
			perror("Cannot open infile ");
		else if (error == 2)
			perror("Memory allocation failed ");
		if (error != 0)
		{
			ft_full_free(pipex, error);
		}
		exit(0);
	}
	return (pid);
}

int	ft_fork(char **argv, char **envp, t_data *pipex)
{
	int	pid;
	int	error;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork : ");
		return (2);
	}
	if (pid == 0)
	{
		error = ft_child(argv, envp, pipex);
		if (error == 1)
			perror("Cannot open infile ");
		else if (error == 2)
			perror("Memory allocation failed ");
		if (error != 0)
		{
			ft_full_free(pipex, error);
		}
		exit(0);
	}
	return (pid);
}

int	ft_fork_l(char **argv, char **envp, t_data *pipex)
{
	int	pid;
	int	error;

	pid = fork();
	if (pid < 0)
		return (perror("Fork : "), 2);
	if (pid == 0)
	{
		if (pipex->here == 1)
			error = ft_child_last2(argv, envp, pipex);
		else
			error = ft_child_last(argv, envp, pipex);
		if (error == 1)
			perror("Cannot open outfile ");
		else if (error == 2)
			perror("Memory allocation failed ");
		if (error != 0)
		{
			ft_full_free(pipex, error);
		}
		exit(0);
	}
	return (pid);
}
