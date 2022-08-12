/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:37:02 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/12 10:52:48 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	*get_command_path(char *command, t_env *envlist)
{
	char	*path_var;
	char	*path;

	path = absolute_relative_path(command);
	if (path == NULL)
	{
		path_var = ft_getenv("PATH", envlist);
		if (path_var[0] == '\0')
		{
			perror("getenv : PATH is not set ");
			return (NULL);
		}
		path = environment_path(command, path_var);
	}
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*craft_path(char *path, char *command)
{
	char	*tmp;
	char	*cmd_path;

	tmp = path;
	path = ft_strjoin(path, "/");
	magic_malloc(ADD, 0, path);
	magic_malloc(FREE, 0, tmp);
	cmd_path = ft_strjoin(path, command);
	magic_malloc(ADD, 0, cmd_path);
	return (cmd_path);
}

char	**magic_split(char *path_var)
{
	char	**paths;
	int		i;

	paths = ft_split(path_var, ':');
	magic_malloc(ADD, 0, paths);
	i = 0;
	while (paths[i])
	{
		magic_malloc(ADD, 0, paths[i]);
		i++;
	}
	return (paths);
}

char	*environment_path(char *command, char *path_var)
{
	char	*cmd_path;
	char	**paths;
	int		i;

	paths = magic_split(path_var);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = craft_path(paths[i], command);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (cmd_path);
		}
		magic_malloc(FREE, 0, cmd_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

char	*absolute_relative_path(char *command)
{
	char	*cmd_path;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		printf("coucou\n");
		if (access(command, F_OK | X_OK) == 0)
		{
			printf("hello\n");
			return (command);
		}
		else
		{
			printf("bonjour\n");
			return (NULL);
		}
	}
	else
	{
		if (command[0] != '.')
		{
			cmd_path = ft_strjoin("./", command);
			magic_malloc(ADD, 0, cmd_path);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		else
		{
			magic_malloc(FREE, 0, cmd_path);
			return (NULL);
		}
	}
}
