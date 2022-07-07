/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:31 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/25 20:49:35 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	ft_child(char **argv, char **envp, t_data *pipex)
{
	char	**arr;
	char	*path;
	int		i;

	i = pipex->index;
	dup2(pipex->fd[(i * 2) - 2], STDIN_FILENO);
	dup2(pipex->fd[(i * 2) + 1], STDOUT_FILENO);
	ft_close_all(pipex->fd, pipex->nbfd);
	if (ft_strncmp(argv[1], "here_doc", 20) == 0)
		arr = ft_split(argv[3 + i], ' ');
	else
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
