#include "minishell.h"
#include <unistd.h>

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char **envtab;
	int	fdinout[2];
	int	error;

	if (redir_open(cmd, fdinout) == 1)
		return (1);
	dup_close_in(mini, cmd, fdinout);
	if (cmd->path == NULL)
	{
		write(2, "Command not found\n", 18); /*GESTION ERREUR*/
		redir_close(mini, cmd, 0);
		return (127);
	}
	if (ft_strncmp(cmd->path, "builtin", 8) == 0)
	{
		error = which_builtin(mini, cmd->args, envlist);
		redir_close(mini, cmd, 1);
		close(mini->std_in);
		close(mini->std_out);
		return (error);
	}
	envtab = ft_convertlist(envlist);
	if (execve(cmd->path, cmd->args, envtab) == -1)
		perror("execve \n");
	redir_close(mini, cmd, 0);
	error = errno;
	return (error);
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