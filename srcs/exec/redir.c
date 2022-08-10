/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:01:45 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/10 12:09:40 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	redir_open_in(t_redirection *redir, t_command *current_cmd);
int	redir_open_out(t_redirection *redir);

/*Ouvre tous les fichiers impliqués dans des redirections*/
int	redir_open(t_command *current_cmd, int fd[2])
{
	int				fdin;
	int				fdout;
	t_redirection	*redir;

	fdin = -1;
	fdout = -1;
	redir = current_cmd->redirection;
	while (redir != NULL)
	{
		if (redir->mode == TRUNC || redir->mode == APPEND)
		{
			fdout = redir_open_out(redir);
		}
		else if (redir->mode == INFILE || redir->mode == DELIMITER)
		{
			fdin = redir_open_in(redir, current_cmd);
		}
		if (fdout == -2 || fdin == -2)
			return (1);
		redir = redir->next;
	}
	fd[0] = fdin;
	fd[1] = fdout;
	return (0);
}

int	redir_open_in(t_redirection *redir, t_command *current_cmd)
{
	if (redir->mode == INFILE)
	{
		redir->fd = open(redir->str, O_RDONLY);
		if (redir->fd < 0)
		{
			print_errors(OPEN_ERROR);
			return (perror(""), -2);
		}
	}
	else if (redir->mode == DELIMITER)
	{
		redir->fd = open_heretmp(current_cmd, 0);
		if (redir->fd < 0)
		{
			print_errors(OPEN_ERROR);
			return (perror(""), -2);
		}
	}
	return (redir->fd);
}

int	redir_open_out(t_redirection *redir)
{
	if (redir->mode == TRUNC)
	{
		redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (redir->fd < 0)
		{
			print_errors(OPEN_ERROR);
			return (perror(""), -2);
		}
	}
	else if (redir->mode == APPEND)
	{
		redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (redir->fd < 0)
		{
			print_errors(OPEN_ERROR);
			return (perror(""), -2);
		}
	}
	return (redir->fd);
}

/*Ferme tous les fichiers impliqués dans des redirections*/
int	redir_close(t_data *mini, t_command *current_cmd, int flag)
{
	t_redirection	*redir;

	redir = current_cmd->redirection;
	while (redir != NULL)
	{
		if (redir->fd != -1)
		{
			if (close(redir->fd) == -1)
				perror("redir_close ");
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
