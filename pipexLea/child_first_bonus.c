/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_first_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:36 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 22:56:31 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_child_first(char **argv, char **envp, t_data *pipex)
{
	int		fdin;
	char	**arr;
	char	*path;

	fdin = open(argv[1], O_RDONLY, 0777);
	if (fdin < 0)
		return (1);
	dup2(fdin, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	ft_close_all(pipex->fd, pipex->nbfd);
	arr = ft_split(argv[2], ' ');
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

int	ft_child_first2(char **argv, char **envp, t_data *pipex)
{
	int		fdin;
	char	**arr;
	char	*path;

	fdin = open("/tmp/pipextmp", O_RDONLY);
	if (fdin < 0)
		return (1);
	dup2(fdin, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	ft_close_all(pipex->fd, pipex->nbfd);
	arr = ft_split(argv[3], ' ');
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

int	ft_heredoc(char *limiter, t_data *pipex)
{
	int		fdtmp;
	int		fdgnl;

	fdtmp = open("/tmp/pipextmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fdtmp < 0)
		ft_full_free(pipex, 4);
	fdgnl = dup(STDIN_FILENO);
	ft_tempfile(limiter, fdgnl, fdtmp);
	close(fdtmp);
	return (0);
}

void	ft_tempfile(char *limiter, int fd, int fdtmp)
{
	char	*line;
	int		stop;

	stop = 0;
	while (1)
	{
		if (stop != 1)
			write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			stop = 1;
			close(fd);
		}
		else
			write(fdtmp, line, ft_strlen(line));
		free(line);
	}
}
