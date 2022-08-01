#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i] != NULL)
	{
		magic_malloc(FREE, 0, tab[i]);
		i++;
	}
	magic_malloc(FREE, 0, tab);
}

char	*get_command_path(char *command, t_env *envlist)
{
	char	*path_var;
	char	*path;

	/*savoir si on a déjà un chemin ou si on doit aller le chercher dans l'env*/
	path = absolute_relative_path(command);
	if (path == NULL)
	{
		path_var = ft_getenv("PATH", envlist);
		if (path_var[0] == '\0')
		{
			perror("getenv : PATH is not set "); /*GESTION ERREUR*/
			return (NULL);
		}
		path = environment_path(command, path_var);
	}
	if (path == NULL)
		return (NULL);
	return (path);
}

char *environment_path(char *command, char *path_var)
{
	char	*cmd_path;
	char	**paths;
	int		i;
	char	*tmp;

	paths = ft_split(path_var, ':');
	magic_malloc(ADD, 0, paths);
	i = 0;
	while (paths[i])
	{
		magic_malloc(ADD, 0, paths[i]);
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		magic_malloc(ADD, 0, paths[i]);
		magic_malloc(FREE, 0, tmp);
		cmd_path = ft_strjoin(paths[i], command);
		magic_malloc(ADD, 0, cmd_path);
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

	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		else
		{
			//perror("Command absolute path "); /*GESTION ERREUR*/
			return (NULL);
		}
	}
	else
	{
		cmd_path = ft_strjoin("./", command);
		magic_malloc(ADD, 0, cmd_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		else
		{
			//perror("Command relative path "); /*GESTION ERREUR*/
			magic_malloc(FREE, 0, cmd_path);
			return (NULL);
		} 
	}
}
