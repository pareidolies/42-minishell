#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/*Une fois que le parser nous a permis de recup un tableau de string*/
/*constitué de la commande et ses argument :*/
int	exe_command(char **commandfull)
{
	char	*path_var;
	char	*path;

	/*savoir si on a déjà un chemin ou si on doit aller le chercher dans l'env*/
	if (commandfull[0] contient un '/')
		path = absolute_relative_path(commandfull[0]);
	else
	{
		path_var = ft_getenv("PATH", envlist);
		if (path_var[0] == '\0')
		{
			perror("getenv error "); /*GESTION ERREUR*/
			return (1);
		}
		path = environment_path(commandfull[0], path_var);
	}
	if (path == NULL)
		this is la mierda, trucs a gerer
	/*maintenant qu'on a le path, on peut executer*/
}

char *environment_path(char *command, char *path_var)
{
	char	*cmd_path;
	char	**paths;
	int		i;
	char	*tmp;

	paths = ft_split(pathline, ':');
	if (paths == NULL)
		return (NULL); /*GESTION ERREUR*/
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free(paths); ////FT_FREE A REFAIRE
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free(paths);
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
			perror("Command absolute path "); /*GESTION ERREUR*/
			return (NULL);
		}
	}
	else
	{
		cmd_path = ft_strjoin("./", command);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		else
		{
			perror("Command relative path "); /*GESTION ERREUR*/
			return (free(cmd_path), NULL);
		} 
	}
}
