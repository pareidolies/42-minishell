#include "minishell.h"
#include <unistd.h>

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char **envtab;
	int	fdinout[2];
	int	error;

	if (redir_open(cmd, fdinout) == 1)
		return (1);
	//printf("IN CHILD, fdinout[0] = %d et fdinout[1] = %d\n", fdinout[0], fdinout[1]);
	dup_close_in(mini, cmd, fdinout);
	if (cmd->path == NULL)
	{
		write(2, "Command not found\n", 18); /*GESTION ERREUR*/
		redir_close(mini, cmd, 0);
		return (1);
	}
	if (ft_strncmp(cmd->path, "builtin", 8) == 0)
	{
		error = which_builtin(mini, cmd->args, envlist);
		redir_close(mini, cmd, 1);
		close(mini->std_in);
		close(mini->std_out);
		magic_malloc(QUIT, 0, NULL);
		return (error);
	}
	envtab = ft_convertlist(envlist);
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
	envtab = magic_malloc(MALLOC, sizeof(char *) * (i + 1), NULL);
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