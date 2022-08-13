/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:16:41 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:43:18 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
		nb_fd++;
		commands = commands->next;
	}
	mini->nb_fd_pipes = (nb_fd - 1) * 2;
	mini->nb_pid = nb_fd;
	mini->std_in = dup(STDIN_FILENO);
	mini->std_out = dup(STDOUT_FILENO);
	return (mini);
}

static int	ft_env_size(t_env *envlist)
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

int	ft_update_status(t_env *envlist)
{
	char	*newvalue;

	newvalue = ft_itoa(g_exit_status);
	magic_malloc(ADD, 0, newvalue);
	update_env("?", newvalue, envlist);
	return (0);
}

int	path_error(t_command *cmd)
{
	if (cmd->cmd == NULL)
	{
		return (0);
	}
	if (cmd->full_cmd[0] == '\0')
	{
		return (0);
	}
	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) != 0)
	{
		return (print_errors_3(EX_ERROR, cmd->cmd));
	}
	return (print_errors_2(127, cmd->args[0]));
}
