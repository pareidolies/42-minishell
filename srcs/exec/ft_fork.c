#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"


pid_t   *multi_fork(t_data *mini)
{
	int			nb;
	pid_t		*pid_tab;
	t_command	*cmd;

	nb = mini->nb_pid;
	cmd = mini->commands;
	pid_tab = magic_malloc(MALLOC, sizeof(pid_t) * nb, NULL);
	while (cmd != NULL)
	{
		pid_tab[cmd->index] = ft_fork(mini, cmd);
		cmd = cmd->next;
	}
    return (pid_tab);
}

pid_t   ft_fork(t_data *mini, t_command *cmd)
{
    pid_t   pid;
    int     error;

    pid = fork();
    if (pid < 0)
	{
		perror("Fork : ");
		error = errno;
		return (error);
	}
    if (pid == 0)
    {
		set_signals_as_child();
        error = ft_child(mini, cmd, mini->envlist);
        if (error != 0)
            magic_malloc(error, 0, NULL);
        else
            magic_malloc(0, 0, NULL);
    }
    return (pid);
}