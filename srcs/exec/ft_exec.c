#include "minishell.h"
#include <fcntl.h>

// int ft_exec(t_command *commands, t_env *envlist)
// {
// 	int	*fd;
// 	int	*pid;

// 	if (commands->next != NULL) //pas de pipe pour une seule cmd
// 	{
// 		fd = open_pipes(commands);
// 		if (ft_strncmp(commands->path, "builtin", 8) == 0)
// 			pid = NULL;
// 		else
// 			pid = malloc
// 	}	
// 	else
// 		fd = NULL;

	
// 	pid
// }

int	exec_no_pipeline(t_command *current_cmd, t_env *envlist)
{
	int	pid;
	int error;
	int	fdinout[2];

	error = 0;
	if (current_cmd->path == NULL)
		return (0);
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
			// do the thing
			printf("I do the thing\n");
			exit(0);
		}
	}
	else //cas des builtin
	{
		redir_open(current_cmd, fdinout);
		//ft_dup(current_cmd, envlist, &fdinout);
		error = which_builtin(current_cmd->args, envlist);
	}
	return (error);
}

// ft_dup(t_command *current_cmd, t_env *envlist, int fd[2])
// {
// 	if (fd[0] == -1) //pas de redir IN
// 	{
// 		if (current_cmd->prev != NULL) // pipe entrant
// 			dup2()
// 	}
// }

int redir_open(t_command *current_cmd, int fd[2])
{
	int				fdin;
	int				fdout;
	t_redirection	*redir;

	fdin = -1;
	fdout = -1;
	redir = current_cmd->redirection;
	while (redir != NULL)
	{
		if (redir->mode == TRUNC || redir->mode == APPEND) //OUT
		{
			if (redir->mode == TRUNC)
			{
				redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (redir->fd < 0)
					return (1); /*GESTION ERREUR*/
			}
			else if (redir->mode == APPEND)
			{
				redir->fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (redir->fd < 0)
					return (1); /*GESTION ERREUR*/
			}
			fdout = redir->fd;
		}
		else if (redir->mode == INFILE || redir->mode == DELIMITER) //IN
		{
			if (redir->mode == INFILE)
			{
				redir->fd = open(redir->str, O_RDONLY);
				if (redir->fd < 0)
					return (1); /*GESTION ERREUR*/
			}
			else if (redir->mode == DELIMITER)
			{
				redir->fd = open("/tmp/crustacestmp", O_RDONLY);
				if (redir->fd < 0)
					return (1); /*GESTION ERREUR*/
			}
			fdin = redir->fd;
		}
		redir = redir->next;
	}
	fd[0] = fdin;
	fd[1] = fdout;
	return (0);
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

int	*open_pipes(t_command *commands)
{
	int	nb_fd;
	int	i;
	int	*fd;
	int	pip[2];

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