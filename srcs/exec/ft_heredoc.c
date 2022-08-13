/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:01:14 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:50:48 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	scan_cmd(t_data *mini);

int	ft_fork_here(t_data *mini)
{
	pid_t	pid;
	int		error;
	int		wstatus;

	pid = fork();
	if (pid < 0)
	{
		error = errno;
		print_errors_2(FORK_ERROR, strerror(error));
		return (error);
	}
	if (pid == 0)
	{
		set_signals_as_heredoc();
		error = scan_cmd(mini);
		close(mini->std_in);
		close(mini->std_out);
		magic_malloc(error, 0, NULL);
	}
	waitpid(pid, &wstatus, 0);
	error = child_status(wstatus);
	return (error);
}

static int	scan_cmd(t_data *mini)
{
	t_redirection	*redir;
	t_command		*cmd;
	int				error;

	cmd = mini->commands;
	while (cmd != NULL)
	{
		redir = cmd->redirection;
		while (redir != NULL)
		{
			if (redir->mode == DELIMITER)
			{
				error = ft_heredoc(mini, cmd, redir);
				if (error != 0)
					return (error);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_heredoc(t_data *mini, t_command *cmd, t_redirection *redir)
{
	int				fdtmp;
	int				fdgnl;
	int				error;

	fdtmp = open_heretmp(cmd, 1);
	if (fdtmp < 0)
	{
		ft_close_all(mini->pipes, mini->nb_fd_pipes);
		return (1);
	}
	fdgnl = dup2(STDIN_FILENO, 60);
	error = ft_tempfile(redir->str, fdgnl, fdtmp);
	close(fdtmp);
	if (error != 0)
		return (error);
	return (0);
}

int	open_heretmp(t_command *cmd, int flag)
{
	int		fdtmp;
	char	*index;
	char	*pathname;

	fdtmp = 0;
	index = ft_itoa(cmd->index);
	magic_malloc(ADD, 0, index);
	pathname = ft_strjoin("/tmp/crustacestmp", index);
	magic_malloc(ADD, 0, pathname);
	if (flag == 2)
		unlink(pathname);
	else if (flag == 1)
		fdtmp = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		fdtmp = open(pathname, O_RDONLY);
	if (fdtmp < 0)
	{
		print_errors_2(OPEN_ERROR, strerror(errno));
		return (-1);
	}
	magic_malloc(FREE, 0, index);
	magic_malloc(FREE, 0, pathname);
	return (fdtmp);
}

int	ft_tempfile(char *str, int fd, int fdtmp)
{
	char	*line;
	char	*limiter;

	line = NULL;
	limiter = ft_strjoin(str, "\n");
	magic_malloc(ADD, 0, limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL
			|| (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0))
		{
			close(fd);
			if (g_exit_status == 130)
				return (130);
			if (line == NULL)
				print_errors_3(HEREDOC_WARNING, limiter);
			break ;
		}
		else
			write(fdtmp, line, ft_strlen(line));
	}
	get_next_line(fd);
	return (0);
}
