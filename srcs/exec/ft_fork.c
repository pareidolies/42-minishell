#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"


pid_t   *multi_fork(t_data *mini)
{
	int			nb;
	pid_t		*pid;
	t_command	*cmd;

	nb = mini->nb_pid;
	cmd = mini->commands;
	pid = magic_malloc(MALLOC, sizeof(pid_t) * nb, NULL);
	while (cmd != NULL)
	{
		pid[cmd->index] = ft_fork(mini, cmd);
		cmd = cmd->next;
	}
    return (pid);
}

pid_t   ft_fork(t_data *mini, t_command *cmd)
{
    pid_t   pid;
    int     error;

    pid = fork();
    if (pid < 0)
	{
		perror("Fork : "); /*GESTION ERREUR*/
		error = errno;
		return (error);
	}
    if (pid == 0)
    {
		set_signals_as_child();
        error = ft_child(mini, cmd, mini->envlist);
        if (error != 0)
            exit(1); /*GESTION ERREUR*/
        else
            exit(0);
    }
    return (pid);
}