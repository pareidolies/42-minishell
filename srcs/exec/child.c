#include "minishell.h"
#include <unistd.h>

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char **envtab;
	int	fdinout[2];

	envtab = ft_convertlist(envlist);
	redir_open(cmd, fdinout);
	dup_close_in(mini, cmd, fdinout);
	if (execve(cmd->path, cmd->args, envtab) == -1)
		perror("Program didn't execute properly.\n");
	/*Tout ce qui suit est appelé uniquement en cas d'erreur de execve*/
	redir_close(mini, cmd, 0);
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