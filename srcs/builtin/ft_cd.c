#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "builtin.h"
#include "minishell.h"

int ft_cd(char **params, t_env *envlist)
{
	char	*current;
	DIR		*directory;

	if (nb_param(params) != 2)
		return (cd_others(params, envlist));
	current = getcwd(NULL, 0);
	if (current == NULL)
	{
		perror("cd (getcwd) ");
		return (1); /*GESTION ERREUR*/
	}
	//printf("current : [%s]\n", current);
	if (access(params[1], F_OK) == 0) //if it exists
	{
		directory = opendir(params[1]);
		if (directory != NULL) //if it is a openable directory
		{
			if (chdir(params[1]) == 0) //if we can change directory
			{
				update_env("OLDPWD", current, envlist);
				free(current);
				if ((current = getcwd(NULL, 0)) == NULL)
				{
					perror("cd (getcwd) ");
					return (1); /*GESTION ERREUR*/
				}
				update_env("PWD", current, envlist);
			}
			else
				perror("minishell: cd: ");/*GESTION ERREUR*/
			closedir(directory);
		}
		else
			write(2, "Not a directory\n", 16);/*GESTION ERREUR*/
	}
	else
		write(2, "No such file or directory\n", 26);/*GESTION ERREUR*/
	free(current);
	return (0);
}

/*début de code pour recup le chemin si besoin*/
	// char	*tmp;
	// char	*path;

	// if (params[0][0] == '/') //chemin absolu
	// 	path = params[0];
	// else if (ft_strchr(params[0], '/') != NULL) //chemin relatif
	// {
	// 	tmp = ft_strjoin(current, "/");
	// 	if (tmp == NULL)
	// 		return (perror("cd "), 2);
	// 	path = ft_strjoin(tmp, params[0]); //PWD + relatif = absolu
	// 	if (path == NULL)
	// 	{
	// 		free(tmp);
	// 		return (perror("cd "), 2);
	// 	}
	// 	free(tmp);
	// }
	

int	cd_others(/*t_command_table *table, */char **params, t_env *envlist)
{
	char	*path;
	char	*current;

	if (nb_param(params) > 2)
	{
		write(2, "cd : too many arguments\n", 24); /*GESTION ERREUR*/
		return (1);
	}
	if (nb_param(params) == 1)
	{
		path = ft_getenv("HOME", envlist);
		current = getcwd(NULL, 0);
		if (current == NULL)
		{
			perror("cd (getcwd) ");
			return (1); /*GESTION ERREUR*/
		}
		if (path[0] == '\0')
		{
			write(2, "cd : HOME not set\n", 18); /*GESTION ERREUR*/
			return (1);
		}
		if (chdir(path) == 0)
		{
			update_env("OLDPWD", current, envlist);
			update_env("PWD", path, envlist);
			return (0);
		}
		else
		{
			perror("cd "); /*GESTION ERREUR*/
			return (2);
		}
	}
	return (0);
}

int	update_env(char *key, char *newvalue, t_env	*envlist)
{
	t_env	*var;

	var = ft_getenv_var(key, envlist);
	if (var == NULL)
	{
		var = ft_new_var_split(key, newvalue);
		if (var == NULL) /*GESTION ERREUR*/
			return (perror("update_env (ft_new_var_split) "), 1);
		ft_lstaddback(&envlist, var);
	}
	else
	{
		if (newvalue != NULL)
		{
			free(var->value);
			var->value = ft_strdup(newvalue);
			if (var->value == NULL)
				return (perror("update_env "), 1);
		}
	}
	return (0);
}

t_env	*ft_new_var_split(char *key, char *value)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror("ft_new_var_split "), NULL); /*GESTION D'ERREUR*/
	var->key = ft_strdup(key);
	if (var->key == NULL)
		return (perror("ft_new_var_split "), NULL);
	if (value != NULL)
	{
		var->value = ft_strdup(value);
		if (var->value == NULL)
			return (perror("ft_new_var_split "), NULL);
	}
	else
		var->value = NULL;
	var->next = NULL;
	return (var);
}
