/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:21:17 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 10:45:03 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int	child_builtin(t_data *mini, t_command *cmd);
int	is_a_dir(char *path);

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char	**envtab;
	int		fdinout[2];
	int		error;

	if (redir_open(cmd, fdinout) == 1)
	{
		ft_close_all(mini->pipes, mini->nb_fd_pipes);
		redir_close(mini, cmd, 0);
		return (1);
	}
	dup_close_in(mini, cmd, fdinout);
	if (cmd->path == NULL)
	{
		redir_close(mini, cmd, 0);
		return (path_error(cmd));
	}
	if (is_a_dir(cmd->path) == 1)
		return(print_errors_3(126, cmd->path));
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

int	is_a_dir(char *path)
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
	// while (path[i + 1] != '\0')
	// {
	// 	i++;
	// }
	// if (path[i] == '/' || (path[i] == '.' && i != 0))
	// 	return (0);
	// else
	// 	return (1);
}

int	child_builtin(t_data *mini, t_command *cmd)
{
	int	error;

	error = which_builtin(mini, cmd->args, mini->envlist);
	redir_close(mini, cmd, 1);
	close(mini->std_in);
	close(mini->std_out);
	return (error);
}

int	ft_env_size(t_env *envlist)
{
	int		i;
	t_env	*var;

	i = 0;
	var = envlist;
	while (var != NULL)
	{
		if (var->value != NULL)
		{
			i++;
		}
		var = var->next;
	}
	return (i);
}

char	**ft_convertlist(t_env *envlist)
{
	int		i;
	t_env	*var;
	char	**envtab;
	char	*tmp;

	var = envlist;
	i = ft_env_size(envlist);
	envtab = magic_malloc(MALLOC, sizeof(char *) * (i + 1), NULL);
	envtab[i] = NULL;
	var = envlist;
	while (var != NULL)
	{
		if (var->value != NULL)
		{
			i--;
			tmp = ft_strjoin(var->key, "=");
			magic_malloc(ADD, 0, tmp);
			envtab[i] = ft_strjoin(tmp, var->value);
			magic_malloc(ADD, 0, envtab[i]);
			magic_malloc(FREE, 0, tmp);
		}
		var = var->next;
	}
	return (envtab);
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
