/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_last_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:46:49 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/25 20:46:58 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_child_last(char **argv, char **envp, t_data *pipex)
{
	int		fdout;
	char	**arr;
	char	*path;
	int		i;

	i = pipex->index;
	fdout = open(argv[pipex->nbpid + 2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fdout < 0)
		return (1);
	dup2(pipex->fd[(i * 2) - 2], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	ft_close_all(pipex->fd, pipex->nbfd);
	arr = ft_split(argv[2 + i], ' ');
	if (arr == NULL)
		return (2);
	path = ft_get_path(arr[0], envp);
	if (path == NULL)
		return (ft_free(arr), 3);
	if (execve(path, arr, envp) == -1)
		perror("Program didn't execute properly.\n");
	ft_free(arr);
	free(path);
	return (4);
}

int	ft_child_last2(char **argv, char **envp, t_data *pipex)
{
	int		fdout;
	char	**arr;
	char	*path;
	int		i;

	i = pipex->index;
	fdout = open(argv[pipex->nbpid + 3], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fdout < 0)
		return (1);
	dup2(pipex->fd[(i * 2) - 2], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	ft_close_all(pipex->fd, pipex->nbfd);
	arr = ft_split(argv[3 + i], ' ');
	if (arr == NULL)
		return (2);
	path = ft_get_path(arr[0], envp);
	if (path == NULL)
		return (ft_free(arr), 3);
	if (execve(path, arr, envp) == -1)
		perror("Program didn't execute properly.\n");
	ft_free(arr);
	free(path);
	return (4);
}
