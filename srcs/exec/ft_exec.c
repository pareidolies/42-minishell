#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_exec(t_command *commands, t_env *envlist)
{
	t_data	*mini;
	// int	*fd;
	// int	*pid;

	mini = ft_init_data(commands, envlist);
	if (mini->nb_pid > 1) //si au moins 2 commandes
	{
		mini->pipes = open_pipes(mini);
		//mini->pid = multi_fork(mini);
	}	
	else
	{
		mini->pipes = NULL;
		mini->pid = NULL;
		exec_no_pipeline(mini, mini->commands, mini->envlist);
	}
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
	return (mini);
}

int	exec_no_pipeline(t_data *mini, t_command *current_cmd, t_env *envlist)
{
	int	pid;
	int error;
	int wstatus;
	int	fdinout[2];

	error = 0;
	if (current_cmd->path == NULL)
	{
		write(2, "Command not found\n", 18); /*GESTION ERREUR*/
		return (0);
	}
	if (ft_strncmp(current_cmd->path, "builtin", 8) != 0) //pas un builtin
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork : ");
			return (2);
		}
		if (pid == 0)
		{
			ft_child(mini, current_cmd, envlist);
			exit(0);
		}
		waitpid(pid, &wstatus, 0);
	}
	else //cas des builtin
	{
		redir_open(current_cmd, fdinout);
		dup_close_in(mini, current_cmd, fdinout);
		error = which_builtin(current_cmd->args, envlist);
		redir_close(current_cmd);
	}
	return (error);
}

int	which_builtin(char **args, t_env *envlist)
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
	// else if (ft_strncmp(args[0], "exit", 5) == 0)
	// 	return (ft_exit(args, envlist));
	return (0);
}