#include "minishell.h"

int ft_exec(t_command *commands, t_env *envlist)
{
	int	*fd;
	int	*pid;

	fd = open_pipes(commands);
	pid
}

int	*open_pipes(t_command *commands)
{
	int	nb_fd;
	int	i;
	int	*fd;
	int	pipe[2];

	nb_fd = 0;
	while (commands != NULL)
		nb_fd++; //nbr de commandes
	nb_fd = (nb_fd - 1) * 2; //nbre de pipes x 2
	fd = malloc(sizeof(int) * nb_fd);
	if (fd == NULL)
		return (NULL); /*GESTION ERREUR MALLOC*/
	i = 0;
	while (i < nb_fd)
	{
		if (pipe(pipe) < 0)
		{
			ft_close_all(fd, i);
			free(pipes);
			perror("Pipe error ");
			return (NULL); /*GESTION ERREUR*/
		}
		fd[i] = pipe[0];
		fd[i + 1] = pipe[1];
		i += 2;
	}
	return (fd);
}

int	ft_close_all(int *fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(fd[i]);
		i++;
	}
	return (0);
}