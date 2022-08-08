#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

/* Return values EN COURS */

// int ft_cd(char **params, t_env *envlist)
// {
// 	char	*current;
// 	DIR		*directory;
// 	int		error;

// 	if (nb_param(params) != 2)
// 		return (cd_others(params, envlist));
// 	error = 0;
// 	current = getcwd(NULL, 0);
// 	if (current == NULL)
// 	{
// 		perror("cd (getcwd) ");
// 		error = errno;
// 		return (error); /*GESTION ERREUR*/
// 	}
// 	if (access(params[1], F_OK) == 0) //if it exists
// 	{
// 		directory = opendir(params[1]);
// 		if (directory != NULL) //if it is a openable directory
// 		{
// 			if (chdir(params[1]) == 0) //if we can change directory
// 			{
// 				update_env("OLDPWD", current, envlist);
// 				free(current);
// 				current = getcwd(NULL, 0);
// 				if (current == NULL)
// 				{
// 					perror("cd (getcwd) ");
// 					error = errno;
// 					return (error); /*GESTION ERREUR*/
// 				}
// 				update_env("PWD", current, envlist);
// 			}
// 			else
// 			{
// 				perror("cd: ");/*GESTION ERREUR*/
// 				error = errno;
// 				return (free(current), error);
// 			}
// 			closedir(directory);
// 		}
// 		else
// 		{
// 			write(2, "Not a directory\n", 16);/*GESTION ERREUR*/
// 			error = 1;
// 		}
// 	}
// 	else
// 	{
// 		write(2, "No such file or directory\n", 26);/*GESTION ERREUR*/
// 		error = 1;
// 	}
// 	free(current);
// 	if (error != 0)
// 		return (error);
// 	return (0);
// }	

// int	cd_others(char **params, t_env *envlist)
// {
// 	char	*path;
// 	char	*current;
// 	int		error;
// 	t_env	*var;

// 	if (nb_param(params) > 2)
// 	{
// 		write(2, "cd : too many arguments\n", 24); /*GESTION ERREUR*/
// 		return (1);
// 	}
// 	if (nb_param(params) == 1)
// 	{
// 		var = ft_getenv_var("HOME", envlist);
// 		if (var == NULL || var->value == NULL)
// 		{
// 			write(2, "cd : HOME not set\n", 18); /*GESTION ERREUR*/
// 			return (1);
// 		}
// 		if (var->value[0] == '\0')
// 			path = ".";
// 		else
// 			path = var->value;
// 		current = getcwd(NULL, 0);
// 		if (current == NULL)
// 		{
// 			perror("cd (getcwd) ");
// 			error = errno;
// 			return (free(current), error); /*GESTION ERREUR*/
// 		}
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

char	*cd_find_path(char **params, t_env *envlist);
int	cd_param_check(char **params, t_env *envlist);

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