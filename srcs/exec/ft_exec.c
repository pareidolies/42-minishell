/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:00:10 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 18:00:22 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int	g_exit_status;

int ft_exec(t_command *commands, t_env *envlist)
{
	t_data	*mini;
	int		wstatus;
	pid_t	wpid;
	int		i;
	int		error;

	mini = ft_init_data(commands, envlist);
	i = 0;
	ft_fork_here(mini);
	if (mini->nb_pid > 1) //si au moins 2 commandes
	{
		printf("COMMANDES MULTIPLES\n");
		mini->pipes = open_pipes(mini);
		mini->pid = multi_fork(mini);
		ft_close_all(mini->pipes, mini->nb_fd_pipes);
		while (i < mini->nb_pid)
		{
			wpid = wait(&wstatus);
			if (wpid == mini->pid[mini->nb_pid - 1])
			{
				if (WIFEXITED(wstatus))
				{
					error = WEXITSTATUS(wstatus); //returns exit status of the child
				}
				if (WIFSIGNALED(wstatus))
					error = WTERMSIG(wstatus); //returns number of the signal 
				g_exit_status = error;
				//ft_update_status(envlist);
				printf("RECUP CODE ERREUR FINAL\n");
			}
			i++;
		}
	}	
	else
	{
		printf("COMMANDE SEULE\n");
		mini->pipes = NULL;
		mini->pid = NULL;
		g_exit_status = exec_no_pipeline(mini, mini->commands, mini->envlist);
		//ft_update_status(envlist);
	}
	close(mini->std_in);
	close(mini->std_out);
	clean_tmpfiles(commands);
	return (0);
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
		nb_fd++; //nbr de commandes
		commands = commands->next;
	}
	mini->nb_fd_pipes = (nb_fd - 1) * 2; //nbre de pipes x 2
	mini->nb_pid = nb_fd;
	mini->std_in = dup(STDIN_FILENO);
	mini->std_out = dup(STDOUT_FILENO);
	//printf("stdin = %d et stdout = %d\n", mini->std_in, mini->std_out);
	return (mini);
}

int	exec_no_pipeline(t_data *mini, t_command *current_cmd, t_env *envlist)
{
	pid_t	pid;
	int 	error;
	int 	wstatus;
	int		fdinout[2];

	error = 0;
	if (current_cmd->path == NULL)
	{
		write(2, "Command not found\n", 18); /*GESTION ERREUR*/
		return (127);
	}
	if (ft_strncmp(current_cmd->path, "builtin", 8) != 0) //pas un builtin
	{
		pid = ft_fork(mini, current_cmd);
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			error = WEXITSTATUS(wstatus); //returns exit status of the child
		if (WIFSIGNALED(wstatus))
			error = WTERMSIG(wstatus); //returns number of the signal that caused the child to terminate
	}
	else //cas des builtin
	{
		if (redir_open(current_cmd, fdinout) == 0)
		{
			dup_close_in(mini, current_cmd, fdinout);
			error = which_builtin(mini, current_cmd->args, envlist);
		}
		redir_close(mini, current_cmd, 1);
	}
	//ft_update_status(envlist);
	g_exit_status = error;
	//printf("status = %d\n", g_exit_status);
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
