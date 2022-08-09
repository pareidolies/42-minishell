/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:03:45 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 18:10:29 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	dup_close_in(t_data *mini, t_command *current_cmd, int fd[2])
{
	int	i;

	i = current_cmd->index;
	if (fd[0] != -1)
	{
		if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
		{
			perror("dup_close_in ");
			return (1);
		}
	}
	else if (fd[0] == -1)
	{
		if (current_cmd->prev != NULL)
		{
			if (dup2(mini->pipes[(i * 2) - 2], STDIN_FILENO) != STDIN_FILENO)
			{
				perror("dup_close_in ");
				return (1);
			}
		}
	}
	return (dup_close_out(mini, current_cmd, fd));
}

int	dup_close_out(t_data *mini, t_command *current_cmd, int fd[2])
{
	int	i;

	i = current_cmd->index;
	if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
		{
			perror("dup_close_out 1 ");
			return (1);
		}
	}
	else if (fd[1] == -1)
	{
		if (current_cmd->next != NULL)
		{
			if (dup2(mini->pipes[(i * 2) + 1], STDOUT_FILENO) != STDOUT_FILENO)
			{
				perror("dup_close_out 2 ");
				return (1);
			}
		}
	}
	ft_close_all(mini->pipes, mini->nb_fd_pipes);
	return (0);
}
