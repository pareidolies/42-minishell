/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:43:40 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 23:26:22 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_check_path(char *pathline, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	paths = ft_split(pathline, ':');
	if (paths == NULL)
		return (free(pathline), NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free(paths);
	return (free(pathline), NULL);
}

char	*ft_get_path(char *cmd, char **envp)
{
	char	*cmd_path;

	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			perror("Command absolute path ");
			return (NULL);
		}
	}
	else if (ft_strchr(cmd, '/') != NULL)
	{
		cmd_path = ft_strjoin("./", cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		else
		{
			perror("Command relative path ");
			return (free(cmd_path), NULL);
		}
	}
	else
		return (ft_env_path(cmd, envp));
}

char	*ft_env_path(char *cmd, char **envp)
{
	int		i;
	char	*pathline;
	char	*cmd_path;

	i = 0;
	while (envp[i] != NULL)
	{
		pathline = ft_strnstr(envp[i], "PATH=", 10);
		if (pathline != NULL)
		{
			pathline = ft_substr(pathline, 5, ft_strlen(pathline));
			if (pathline == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (pathline == NULL)
		write(2, "No PATH informations in env.\n", 29);
	cmd_path = ft_check_path(pathline, cmd);
	if (cmd_path == NULL)
		write(2, "Command not found.\n", 19);
	return (cmd_path);
}
