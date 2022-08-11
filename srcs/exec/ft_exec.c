/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:00:10 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/11 14:43:19 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int	g_exit_status;

int	ft_exec(t_command *commands, t_env *envlist)
{
	t_data	*mini;
	int		error;
	
	mini = ft_init_data(commands, envlist);
	error = ft_fork_here(mini);
	if (error != 0)
	{
		clean_exec(mini);
		g_exit_status = error;
		return (error);
	}
	if (mini->nb_pid > 1)
		g_exit_status = exec_pipeline(mini);
	else
	{
		mini->pipes = NULL;
		mini->pid = NULL;
		g_exit_status = exec_no_pipeline(mini, mini->commands, mini->envlist);
		if (g_exit_status == 130)
		ft_putstr_fd("\n", 2);
		if (g_exit_status == 131)
		ft_putstr_fd("Quit\n", 2);
	}
	clean_exec(mini);
	return (0);
}

int	exec_pipeline(t_data *mini)
{
	int		i;
	pid_t	wpid;
	int		wstatus;
	int		error;
	int		tmp;

	i = -1;
	error = -1;
	mini->pipes = open_pipes(mini);
	mini->pid = multi_fork(mini);
	ft_close_all(mini->pipes, mini->nb_fd_pipes);
	while (++i < mini->nb_pid)
	{
		wpid = wait(&wstatus);
		tmp = child_status(wstatus);
		if (wpid == mini->pid[mini->nb_pid - 1] && error == -1)
			error = tmp;
		if ((tmp == 130 || tmp == 131) && error == -1)
			error = tmp;
	}
	if (error == 130)
		ft_putstr_fd("\n", 2);
	if (error == 131)
		ft_putstr_fd("Quit\n", 2);
	return (error);
}

t_data	*ft_init_data(t_command *commands, t_env *envlist)
{
	t_data	*mini;
	int		nb_fd;

	mini = magic_malloc(MALLOC, sizeof(t_data), NULL);
	mini->commands = commands;
	mini->envlist = envlist;
	nb_fd = 0;
	while (commands != NULL)
	{
		commands->index = nb_fd;
		nb_fd++;
		commands = commands->next;
	}
	mini->nb_fd_pipes = (nb_fd - 1) * 2;
	mini->nb_pid = nb_fd;
	mini->std_in = dup(STDIN_FILENO);
	mini->std_out = dup(STDOUT_FILENO);
	return (mini);
}

int	exec_no_pipeline(t_data *mini, t_command *current_cmd, t_env *envlist)
{
	pid_t	pid;
	int		error;
	int		wstatus;
	int		fdinout[2];

	if (current_cmd->path == NULL)
		return (print_errors_2(127, current_cmd->args[0]));
	if (ft_strncmp(current_cmd->path, "builtin", 8) != 0)
	{
		pid = ft_fork(mini, current_cmd);
		waitpid(pid, &wstatus, 0);
		error = child_status(wstatus);
	}
	else
	{
		if (redir_open(current_cmd, fdinout) == 0)
		{
			dup_close_in(mini, current_cmd, fdinout);
			error = which_builtin(mini, current_cmd->args, envlist);
		}
		else
			error = 1;
		redir_close(mini, current_cmd, 1);
	}
	return (error);
}

int	which_builtin(t_data *mini, char **args, t_env *envlist)
{
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, envlist));
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		return (ft_echo(args));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (ft_env(args, envlist));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (ft_export(args, envlist));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (ft_unset(args, envlist));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (ft_pwd(args));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(mini, args, envlist));
	return (0);
}
