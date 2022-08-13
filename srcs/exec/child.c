/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:21:17 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:16:02 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

static int	redir_error(t_data *mini, t_command *cmd);
static int	is_a_dir(char *path);
static int	child_builtin(t_data *mini, t_command *cmd);

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char	**envtab;
	int		fdinout[2];
	int		error;

	if (redir_open(cmd, fdinout) == 1)
		return (redir_error(mini, cmd));
	dup_close_in(mini, cmd, fdinout);
	if (cmd->path == NULL)
	{
		redir_close(mini, cmd, 0);
		return (path_error(cmd));
	}
	if (is_a_dir(cmd->path) == 1)
		return (print_errors_3(126, cmd->path));
	if (ft_strncmp(cmd->path, "builtin", 8) == 0)
	{
		error = child_builtin(mini, cmd);
		return (error);
	}
	envtab = ft_convertlist(envlist);
	if (execve(cmd->path, cmd->args, envtab) == -1)
		redir_close(mini, cmd, 0);
	return (perror("execve"), 126);
}

static int	is_a_dir(char *path)
{
	int	i;
	DIR	*directory;

	i = 0;
	directory = opendir(path);
	if (directory != NULL)
	{
		closedir(directory);
		return (1);
	}
	else
		return (0);
}

static int	child_builtin(t_data *mini, t_command *cmd)
{
	int	error;

	error = which_builtin(mini, cmd->args, mini->envlist);
	redir_close(mini, cmd, 1);
	close(mini->std_in);
	close(mini->std_out);
	return (error);
}

static int	redir_error(t_data *mini, t_command *cmd)
{
	ft_close_all(mini->pipes, mini->nb_fd_pipes);
	redir_close(mini, cmd, 0);
	return (1);
}

int	child_status(int wstatus)
{
	int	error;

	error = 0;
	if (WIFEXITED(wstatus))
		error = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		error = WTERMSIG(wstatus) + 128;
	}
	return (error);
}
