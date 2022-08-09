/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:01:45 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 18:01:57 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*Ouvre tous les fichiers impliqués dans des redirections*/
int redir_open(t_command *current_cmd, int fd[2])
{
	int				fdin;
	int				fdout;
	t_redirection	*redir;

	fdin = -1;
	fdout = -1;
	redir = current_cmd->redirection;
	printf("VERIF DES REDIRECTIONS\n");
	while (redir != NULL)
	{
		if (redir->mode == TRUNC || redir->mode == APPEND) //OUT
		{
			printf("REDIR SORTANTE\n");
			if (redir->mode == TRUNC)
			{
				redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (redir->fd < 0)
					return (perror("redir_open "), 1); /*GESTION ERREUR*/
			}
			else if (redir->mode == APPEND)
			{
				printf("mode append\n");
				redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (redir->fd < 0)
					return (perror("redir_open "), 1); /*GESTION ERREUR*/
			}
			fdout = redir->fd;
		}
		else if (redir->mode == INFILE || redir->mode == DELIMITER) //IN
		{
			printf("REDIR ENTRANTE\n");
			if (redir->mode == INFILE)
			{
				redir->fd = open(redir->str, O_RDONLY);
				if (redir->fd < 0)
					return (perror("redir_open "), 1); /*GESTION ERREUR*/
			}
			else if (redir->mode == DELIMITER)
			{
				redir->fd = open_heretmp(current_cmd, 0);
				if (redir->fd < 0)
					return (perror("redir_open "), 1); /*GESTION ERREUR*/
			}
			fdin = redir->fd;
		}
		redir = redir->next;
	}
	fd[0] = fdin;
	fd[1] = fdout;
	return (0);
}

/*Ferme tous les fichiers impliqués dans des redirections*/
int redir_close(t_data *mini, t_command *current_cmd, int flag)
{
	t_redirection	*redir;

	redir = current_cmd->redirection;
	while (redir != NULL)
	{
		if (redir->fd != -1)
		{
			if (close(redir->fd) == -1)
				perror("redir_close "); /*GESTION ERREUR*/
		}
		redir = redir->next;
	}
    if (flag == 1)
    {
        dup2(mini->std_in, STDIN_FILENO);
        dup2(mini->std_out, STDOUT_FILENO);
    }
	return (0);
}

int	*open_pipes(t_data *mini)
{
	int	nb_fd;
	int	i;
	int	*fd;
	int	pip[2];

	nb_fd = mini->nb_fd_pipes;
	fd = magic_malloc(MALLOC, sizeof(int) * nb_fd, NULL);
	i = 0;
	printf("OPENING PIPES\n");
	while (i < nb_fd)
	{
		if (pipe(pip) < 0)
		{
			ft_close_all(fd, i);
			free(fd);
			perror("Pipe error ");
			return (NULL); /*GESTION ERREUR*/
		}
		fd[i] = pip[0];
		fd[i + 1] = pip[1];
		i += 2;
	}
	i = 0;
	while (i < nb_fd)
	{
		printf("fd[%d] : %d\n", i, fd[i]);
		i++;
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
