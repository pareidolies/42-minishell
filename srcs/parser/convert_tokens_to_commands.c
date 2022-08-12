/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens_to_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:15:58 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 22:40:32 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_full_cmd_and_redir(t_token *current, t_command *node)
{
	char	*tmp;

	while (current && current->type != T_PIPE)
	{
		if (current->type == T_LITERAL || current->type == T_EXPORT)
		{
			tmp = ft_strjoin(node->full_cmd, STR_SPACE);
			magic_malloc(ADD, 0, tmp);
			node->full_cmd = ft_strjoin(tmp, current->expanded_token);
			magic_malloc(FREE, 0, current->expanded_token);
			magic_malloc(ADD, 0, node->full_cmd);
			magic_malloc(FREE, 0, tmp);
		}
		else if (current->type == T_LESS || current->type == T_GREATER
			|| current->type == T_D_LESS || current->type == T_D_GREATER)
		{
			if (!node->redirection)
				node->redirection = create_redirection(current->next);
			else
				add_redirection(current->next, node->redirection);
		}
		current = current->next;
	}
}

void	add_args2(t_command *node, t_env *envlist)
{
	char	*str;
	int		i;

	if (node->args[0] && (ft_strncmp(node->args[0], "export", 7) == 0 || ft_strncmp(node->args[0], "echo", 5) == 0))
	{
		i = 1;
		while (node->args[i])
		{
			if (is_export_expand(node->args[i]))
			{
				str = node->args[i];
				node->args[i] = create_expanded_token(str, envlist);
			}
			i++;
		}
	}
}

void	add_args(t_command *node, t_env *envlist)
{
	char	*tmp;
	int		i;

	node->args = split_parser(node->full_cmd, SPACE);///////////
	if (node != NULL)
		magic_malloc(ADD, 0, node->args);
	i = 0;
	while (node->args[i])
	{
		magic_malloc(ADD, 0, node->args[i]);
		tmp = withdraw_quotes(node->args[i]);
		magic_malloc(ADD, 0, tmp);
		magic_malloc(FREE, 0, node->args[i]);
		node->args[i] = ft_strdup(tmp);
		magic_malloc(ADD, 0, node->args[i]);
		magic_malloc(FREE, 0, tmp);
		i++;
	}
	add_args2(node, envlist);
}

void	fill_command(t_token *list, t_command *cell, t_env *envlist)
{
	t_token		*current;
	t_command	*node;

	node = cell;
	while (node->next != NULL)
		node = node->next;
	if (node->cmd != NULL)
	{
		node->full_cmd = ft_strdup(node->cmd);////////
		magic_malloc(ADD, 0, node->full_cmd);
	}
	current = list;
	add_full_cmd_and_redir(current, node);
	if (node->cmd == NULL)
	{
		node->path = NULL;
		return;
	}
	add_args(node, envlist);//////////////////////////////////
	if (!node->args[0] || is_builtin(node->args[0]) == 2)
		node->path = NULL;
	else if (is_builtin(node->args[0]) == 1)
	{
		node->path = ft_strdup("builtin");
		magic_malloc(ADD, 0, node->path);
	}
	else
		node->path = get_command_path(node->args[0], envlist);
}

t_command	*convert_tokens_to_commands(t_token *list, t_env *envlist)
{
	t_command	*result;
	t_token		*current;

	current = list;
	result = create_command(current);
	fill_command(current, result, envlist);///////
	while (current->next && current->next->next)
	{
		if ((ft_strncmp(current->next->token, STR_PIPE, \
			ft_strlen(current->next->token)) == 0))
		{
			add_command(current->next->next, result);
			fill_command(current->next->next, result, envlist);
		}
		current = current->next;
	}
	return (result);
}
