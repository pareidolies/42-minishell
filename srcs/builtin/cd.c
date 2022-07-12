#include <unistd.h>
#include "libft.h"
#include "builtin.h"

int ft_cd(char **params)
{
	char	*current;
	char	*path;

	if (nb_param(params) != 1)
		return (cd_others(params))
	current = getcwd(NULL, 0);
	if (current == NULL)
	{
		perror(cd (getcwd) );
		return (1); /*GESTION ERREUR*/
	}
	printf("current : [%s]\n", current);
	path = strjoin(current, )


}

int	cd_others(char **params)
{
	char	*path;

	if (nb_param(params) > 1)
	{
		write(2, "cd : too many arguments\n", 24); /*GESTION ERREUR*/
		return (1);
	}
	if (nb_param(params) == 0)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			write(2, "HOME variable is not set.\n", 26); /*GESTION ERREUR*/
			return (1);
		}
		if (chdir(path) == 0)
			update_env(current, path);
		else
		{
			perror("cd "); /*GESTION ERREUR*/
			return (2);
		}
	}
}

int	update_env(char *currentpwd, char *newpwd)
{
	char	*oldpwd;
	char	*pwd;
	int		i;

	i = 0;
	oldpwd = getenv("OLDPWD");
	if (oldpwd == NULL)
		/*GESTION ERREUR*/
	while ()
}