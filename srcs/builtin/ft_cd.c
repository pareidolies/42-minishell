/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:09:12 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/12 10:43:28 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

char	*cd_find_path(char **params, t_env *envlist);
int		cd_param_check(char **params, t_env *envlist);

int	cd_update(char *current, t_env *envlist)
{
	int	error;

	update_env("OLDPWD", current, envlist);
	free(current);
	current = getcwd(NULL, 0);
	if (current == NULL)
	{
		perror("cd (getcwd) ");
		error = errno;
		return (error);
	}
	update_env("PWD", current, envlist);
	free(current);
	return (0);
}

int	cd_dir_checks(char *pathname, char *current, t_env *envlist)
{
	int	error;
	DIR	*directory;

	directory = opendir(pathname);
	if (directory != NULL)
	{
		if (chdir(pathname) == 0)
			error = cd_update(current, envlist);
		else
		{
			perror("cd: ");
			error = 1;
		}
		if (error != 0)
			return (error);
		closedir(directory);
	}
	else
	{
		write(2, "Not a directory\n", 16);
		return (1);
	}
	return (0);
}

int	ft_cd(char **params, t_env *envlist)
{
	char	*current;
	char	*path;
	int		error;

	error = cd_param_check(params, envlist);
	if (error != 0)
		return (error);
	current = getcwd(NULL, 0);
	if (current == NULL)
	{
		current = ft_strdup(ft_getenv("PWD", envlist));
		if (current == NULL)
		return (perror("cd: "), 1);
	}
	path = cd_find_path(params, envlist);
	if (access(path, F_OK) == 0)
		error = cd_dir_checks(path, current, envlist);
	else
	{
		write(2, "cd: No such file or directory\n", 30);
		error = 1;
		free(current);
	}
	return (error);
}

int	cd_param_check(char **params, t_env *envlist)
{
	t_env	*var;

	if (nb_param(params) > 2)
	{
		write(2, "cd : too many arguments\n", 24);
		return (1);
	}
	var = ft_getenv_var("HOME", envlist);
	if (nb_param(params) == 1 && (var == NULL || var->value == NULL))
	{
		write(2, "cd : HOME not set\n", 18);
		return (1);
	}
	return (0);
}

char	*cd_find_path(char **params, t_env *envlist)
{
	t_env	*var;
	char	*path;

	if (nb_param(params) == 1)
	{
		var = ft_getenv_var("HOME", envlist);
		if (var->value[0] == '\0')
			path = ".";
		else
			path = var->value;
	}
	else
		path = params[1];
	return (path);
}
