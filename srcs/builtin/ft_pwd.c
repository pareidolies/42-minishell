#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "builtin.h"

/*voir si expansion $VAR ici ou faite avant*/
int	ft_pwd(char **params)
{
	char		*path;
	size_t		len;

	if (nb_param(params) > 1 && params[1][0] == '-')
    {
        write(2, "pwd : Invalid option\n", 21);/*GESTION ERREUR*/
        return (1);
    }
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