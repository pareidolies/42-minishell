#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_fork_here(t_data *mini)
{
	pid_t	pid;
	int		error;
	int		wstatus;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork : "); /*GESTION ERREUR*/
		error = errno;
		return (error);
	}
    if (pid == 0)
    {
		set_signals_as_child();
        error = ft_heredoc(mini);
		close(mini->std_in);
		close(mini->std_out);
		magic_malloc(error, 0, NULL); /*GESTION ERREUR*/
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		printf("\n\ncoucou\n\n");
	}
	return (0);
}

int	ft_heredoc(t_data *mini)
{
	int		        fdtmp;
	int		        fdgnl;
	t_redirection   *redir;
	t_command       *cmd;

	cmd = mini->commands;
	while (cmd != NULL)
	{
		redir = cmd->redirection;
		while (redir != NULL)
		{
			if (redir->mode == DELIMITER)
			{
				fdtmp = open_heretmp(cmd, 1);
				fdgnl = dup(STDIN_FILENO);
				ft_tempfile(redir->str, fdgnl, fdtmp);
				close(fdtmp);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	open_heretmp(t_command *cmd, int flag)
{
	int 	fdtmp;
	char	*index;
	char	*pathname;
	
	fdtmp = 0;
	index = ft_itoa(cmd->index);
	magic_malloc(ADD, 0, index);
	pathname = ft_strjoin("/tmp/crustacestmp", index);
	magic_malloc(ADD, 0, pathname);
	if (flag == 3)
		unlink(pathname);
	else if (flag == 1)
		fdtmp = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		fdtmp = open(pathname, O_RDONLY);
	if (fdtmp < 0)
	{
		perror("open_heretmp ");
		magic_malloc(1, 0, NULL);
	}
	magic_malloc(FREE, 0, index);
	magic_malloc(FREE, 0, pathname);
	return (fdtmp);
}

int	clean_tmpfiles(t_command *commands)
{
	t_command		*cmd;
	t_redirection	*redir;

	cmd = commands;
	while (cmd != NULL)
	{
		redir = cmd->redirection;
		while (redir != NULL)
		{
			if (redir->mode == DELIMITER)
			{
				open_heretmp(cmd, 3);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	ft_tempfile(char *str, int fd, int fdtmp)
{
	char	*line;
	int		stop;
	char	*limiter;

	stop = 0;
	limiter = ft_strjoin(str, "\n");
	magic_malloc(ADD, 0, limiter);
	while (stop != 1)
	{
		//if (stop != 1)
		write(1, "> ", 2);
		line = get_next_line(fd);
		//magic_malloc(ADD, 0, line);
		if (line == NULL)
		{
			//!\Attention ce message s'affiche aussi en cas de sortie normale
			ft_putstr_fd_color(HEREDOC_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
			ft_putstr_fd_color(limiter, 2, ANSI_COLOR_LIGHT_RED);
			//faire une sortie propre car leaks pour ctrl-D
			close (fd);
			//stop = 1;
			//magic_malloc(0, 0, NULL);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			stop = 1;
			close(fd);
		}
		else
			write(fdtmp, line, ft_strlen(line));
		free(line);
		//magic_malloc(FREE, 0, line);
	}
	get_next_line(fd);
	magic_malloc(FREE, 0, limiter);
}