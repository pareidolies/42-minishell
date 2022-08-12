/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:54:41 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 19:13:34 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_redirection *list)
{
	t_redirection	*current;
	t_redirection	*tmp;

	current = list;
	while (current)
	{
		magic_malloc(FREE, 0, current->str);
		tmp = current->next;
		magic_malloc(FREE, 0, current);
		current = tmp;
	}
}

void	free_commands(t_command *list)
{
	t_command	*current;
	t_command	*tmp;
	int			i;

	current = list;
	printf("goyave1\n");
	while (current)
	{
		printf("goyave2\n");
		magic_malloc(FREE, 0, current->cmd);
		printf("goyave3\n");
		magic_malloc(FREE, 0, current->full_cmd);
		printf("goyave4\n");
		magic_malloc(FREE, 0, current->path);
		i = 0;
		printf("goyave4.5\n");
		while (current->args != NULL && current->args[i])
		{
			magic_malloc(FREE, 0, current->args[i]);
			i++;
		}
		printf("goyave5\n");
		free_redirections(current->redirection);
		printf("goyave6\n");
		tmp = current->next;
		printf("goyave7\n");
		current = tmp;
	}
}

void	free_tokens(t_token *list)
{
	t_token	*current;
	t_token	*tmp;

	current = list;
	while (current)
	{
		magic_malloc(FREE, 0, current->token);
		tmp = current->next;
		magic_malloc(FREE, 0, current);
		current = tmp;
	}
}
