/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:31:46 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:17:32 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstaddback(t_env **alst, t_env *new)
{
	t_env	*elt;

	if (*alst == NULL)
		*alst = new;
	else
	{
		elt = *alst;
		while (elt->next != NULL)
			elt = elt->next;
		elt->next = new;
	}
}

void	ft_clean_list(t_env	*envlist)
{
	t_env	*tmp;

	while (envlist != NULL)
	{
		magic_malloc(FREE, 0, envlist->key);
		magic_malloc(FREE, 0, envlist->value);
		tmp = envlist->next;
		magic_malloc(FREE, 0, envlist);
		envlist = tmp;
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		magic_malloc(FREE, 0, tab[i]);
		i++;
	}
	magic_malloc(FREE, 0, tab);
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
				open_heretmp(cmd, 2);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	clean_exec(t_data *mini, char *input)
{
	close(mini->std_in);
	close(mini->std_out);
	clean_tmpfiles(mini->commands);
	magic_malloc(FREE, 0, mini->pipes);
	magic_malloc(FREE, 0, mini->pid);
	free_commands(mini->commands);
	magic_malloc(FREE, 0, mini);
	free(input);
	return (0);
}
