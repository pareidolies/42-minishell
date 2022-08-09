/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:21:17 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 17:52:46 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ft_child(t_data *mini, t_command *cmd, t_env *envlist)
{
	char	**envtab;
	int		fdinout[2];
	int		error;

	if (redir_open(cmd, fdinout) == 1)
		return (1);
	dup_close_in(mini, cmd, fdinout);
	if (cmd->path == NULL)
	{
		redir_close(mini, cmd, 0);
		return (print_errors(127));
	}
	if (ft_strncmp(cmd->path, "builtin", 8) == 0)
	{
		error = which_builtin(mini, cmd->args, envlist);
		redir_close(mini, cmd, 1);
		close(mini->std_in);
		close(mini->std_out);
		return (error);
	}
	envtab = ft_convertlist(envlist);
	if (execve(cmd->path, cmd->args, envtab) == -1)
		redir_close(mini, cmd, 0);
	return (perror("execve \n"), 126);
}

int	ft_env_size(t_env *envlist)
{
	int		i;
	t_env	*var;

	i = 0;
	var = envlist;
	while (var != NULL)
	{
		i++;
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
		i--;
		tmp = ft_strjoin(var->key, "=");
		magic_malloc(ADD, 0, tmp);
		envtab[i] = ft_strjoin(tmp, var->value);
		magic_malloc(ADD, 0, envtab[i]);
		magic_malloc(FREE, 0, tmp);
		var = var->next;
	}
	return (envtab);
}
