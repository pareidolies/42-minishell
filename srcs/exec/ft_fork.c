/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:35:37 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/12 16:03:41 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include "minishell.h"

pid_t	*multi_fork(t_data *mini)
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

pid_t	ft_fork(t_data *mini, t_command *cmd)
{
	pid_t	pid;
	int		error;

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
		{
			close(mini->std_in);
			close(mini->std_out);
			magic_malloc(error, 0, NULL);
		}
		else
			magic_malloc(0, 0, NULL);
	}
	return (pid);
}
