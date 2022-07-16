#include <stdio.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

/*voir si expansion $VAR ici ou faite avant*/
int	ft_pwd(char **params)
{
	char	*path;
	int		len;

	/* /!\ verif des arguments est différente entre bash et zsh*/
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd ");
		return (1); /*GESTION ERREUR*/
	}
	len = printf("%s\n", path);
	if (len != ft_strlen(path))
	{
		free(path);
		return (2);
	}
	free(path);
	return (0);
}