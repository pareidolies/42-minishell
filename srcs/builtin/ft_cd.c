/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:13:06 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/07 23:16:50 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

/* Return values OK */

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
		return (error); /*GESTION ERREUR*/
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
	if (directory != NULL) //if it is a openable directory
	{
		if (chdir(pathname) == 0) //if we can change directory
			error = cd_update(current, envlist);
		else
		{
			perror("cd: ");/*GESTION ERREUR*/
			error = errno;
		}
		if (error != 0)
			return (error);
		closedir(directory);
	}
	else
	{
		write(2, "Not a directory\n", 16);/*GESTION ERREUR*/
		return (1);
	}
	return (0);
}

int ft_cd(char **params, t_env *envlist)
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
		perror("cd (getcwd) ");
		error = errno;
		return (error); /*GESTION ERREUR*/
	}
	path = cd_find_path(params, envlist);
	if (access(path, F_OK) == 0) //if path exists
		error = cd_dir_checks(path, current, envlist);
	else
	{
		write(2, "No such file or directory\n", 26);/*GESTION ERREUR*/
		error = 1;
		free(current);
	}
	return (error);
}

int	cd_param_check(char **params, t_env *envlist)
{
	int		error;
	t_env	*var;

	error = 0;
	if (nb_param(params) > 2)
		error += write(2, "cd : too many arguments\n", 24); /*GESTION ERREUR*/
	var = ft_getenv_var("HOME", envlist);
	if (nb_param(params) == 1 && (var == NULL || var->value == NULL))
		error += write(2, "cd : HOME not set\n", 18); /*GESTION ERREUR*/
	return (error);
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

// int	cd_others(char **params, t_env *envlist)
// {
// 	char	*path;
// 	char	*current;
// 	int		error;
// 	t_env	*var;

// 	error = 0;
	
	
// 	current = getcwd(NULL, 0);
// 	if (current == NULL)
// 	{
// 		perror("cd (getcwd) ");
// 		error = errno;
// 		return (free(current), error); /*GESTION ERREUR*/
// 	}
// 		if (chdir(path) == 0)
// 		{
// 			update_env("OLDPWD", current, envlist);
// 			update_env("PWD", path, envlist);
// 			return (free(current), 0);
// 		}
// 		else
// 		{
// 			perror("cd "); /*GESTION ERREUR*/
// 			error = errno;
// 			return (free(current), error);
// 		}
// 		free(current);
// 	}
// 	return (0);
// }

