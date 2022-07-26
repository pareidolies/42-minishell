#include "minishell.h"

int ft_exec(t_command *commands, t_env *envlist)
{
	int	*fd;
	int	*pid;

	if (commands->next != NULL) //pas de pipe pour une seule cmd
	{
		fd = open_pipes(commands);
		if (ft_strncmp(commands->path, "builtin", 8) == 0)
			pid = NULL;
		else
			pid = malloc
	}	
	else
		fd = NULL;

	
	pid
}

int	exec_no_pipeline(t_command *commands, t_env *envlist)
{
	int	pid;
	int error;

	if (ft_strncmp(commands->path, "builtin", 8) != 0) //pas un builtin
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork : ");
			return (2);
		}
		if (pid == 0)
		{
			do the thing
		}
	}
	else //cas des builtin
	{
		redir_open(commands, envlist);
		error = which_builtin(commands->args, envlist);
	}
	return (error);
}

redir_open(t_command *commands, t_env *envlist)
{
	int				fdin;
	int				fdout;
	t_redirection	*redir;

	fdin = 0;
	fdout = 1;
	redir = commands->redirection;
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
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(args, envlist));
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