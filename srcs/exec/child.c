#include "minishell.h"
#include <unistd.h>

int	ft_child(t_command *cmd, t_env *envlist)
{
	char **envtab;

	envtab = ft_convertlist(envlist);
	// if (cmd->path == NULL)
	// {
	// 	write(2, "Command not found\n", 18);
	// 	magic_malloc(QUIT, 0, NULL);
	// }
	if (execve(cmd->path, cmd->args, envtab) == -1)
		perror("Program didn't execute properly.\n");
	magic_malloc(QUIT, 0, NULL);
	//ft_free_tab(envtab);
	return (1);
}

char	**ft_convertlist(t_env *envlist)
{
	int		i;
	t_env	*var;
	char	**envtab;
	char	*tmp;

	i = 0;
	var = envlist;
	while (var != NULL)
	{
		i++;
		var = var->next;
	}
	envtab = magic_malloc(MALLOC, sizeof(char *) * i, NULL);
	i = 0;
	var = envlist;
	while (var != NULL)
	{
		tmp = ft_strjoin(var->key, "=");
		magic_malloc(ADD, 0, tmp);
		envtab[i] = ft_strjoin(tmp, var->value);
		magic_malloc(ADD, 0, envtab[i]);
		magic_malloc(FREE, 0, tmp);
		i++;
		var = var->next;
	}
	envtab[i] = NULL;
	return (envtab);
}