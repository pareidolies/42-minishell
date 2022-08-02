#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	dup_close_in(t_data *mini, t_command *current_cmd, int fd[2])
{
    int i;

    i = current_cmd->index;
	printf("i = %d : fd[0] = %d\n", i, fd[0]);
	if (fd[0] != -1) //redir IN
	{
		if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
		{
			perror("dup_close_in 1 ");
			return (1); /*GESTION ERREUR*/
		}
	}
	else if (fd[0] == -1) //pas de redir IN
	{
		if (current_cmd->prev != NULL) // pipe entrant
		{
			if (dup2(mini->pipes[(i * 2) - 2], STDIN_FILENO) != STDIN_FILENO)
			{
				perror("dup_close_in 2 ");
				return (1); /*GESTION ERREUR*/
			}
		}
	}
	return (dup_close_out(mini, current_cmd, fd));
}

int	dup_close_out(t_data *mini, t_command *current_cmd, int fd[2])
{
    int i;

    i = current_cmd->index;
	printf("i = %d : fd[1] = %d\n", i, fd[1]);
	if (fd[1] != -1) //redir OUT
	{
		if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
		{
			perror("dup_close_out 1 ");
			return (1); /*GESTION ERREUR*/
		}
	}
	else if (fd[1] == -1) //pas de redir OUT
	{
		if (current_cmd->next != NULL) // pipe sortant
		{
			printf("fd = %d\n", mini->pipes[(i * 2) + 1]);
			if (dup2(mini->pipes[(i * 2) + 1], STDOUT_FILENO) != STDOUT_FILENO)
			{
				perror("dup_close_out 2 ");
				return (1); /*GESTION ERREUR*/
			}
		}
	}
	ft_close_all(mini->pipes, mini->nb_fd_pipes);
	return (0);
}