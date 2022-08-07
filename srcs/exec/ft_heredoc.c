#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

int	ft_heredoc(t_data *mini)
{
	int		        fdtmp;
	int		        fdgnl;
	t_redirection   *redir;
	t_command       *cmd;
	// pid_t			pid;

	// pid = fork();
	// if (pid == 0)
	// {
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
		//exit(0);
	//}
	return (0);
}

int	open_heretmp(t_command *cmd, int flag)
{
	int 	fdtmp;
	char	*index;
	char	*pathname;
	
	index = ft_itoa(cmd->index);
	magic_malloc(ADD, 0, index);
	pathname = ft_strjoin("/tmp/crustacestmp", index);
	//printf("pathname = %s\n", pathname);
	magic_malloc(ADD, 0, pathname);
	if (flag == 1)
		fdtmp = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		fdtmp = open(pathname, O_RDONLY);
	magic_malloc(FREE, 0, index);
	magic_malloc(FREE, 0, pathname);
	//printf("tmp est ouvert\n");
	return (fdtmp);
}

void	ft_tempfile(char *str, int fd, int fdtmp)
{
	char	*line;
	int		stop;
	char	*limiter;

	stop = 0;
	limiter = ft_strjoin(str, "\n");
	magic_malloc(ADD, 0, limiter);
	while (1)
	{
		if (stop != 1)
			write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL)
		{
			//printf("je sors\n");
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
	}
	magic_malloc(FREE, 0, limiter);
}