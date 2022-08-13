/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:02:30 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:14:37 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(t_token *list)
{
	t_command	*result;
	t_token		*current;

	result = magic_malloc(MALLOC, sizeof(t_command), NULL);
	current = list;
	while (current->next && current->type != T_LITERAL
		&& current->type != T_PIPE)
		current = current->next;
	if (current->type == T_LITERAL)
	{
		result->cmd = ft_strdup(current->expanded_token);
		current->type = T_CMD;
		magic_malloc(ADD, 0, result->cmd);
		magic_malloc(FREE, 0, current->expanded_token);
	}
	else
		result->cmd = NULL;
	result->full_cmd = NULL;
	result->prev = NULL;
	result->next = NULL;
	result->redirection = NULL;
	result->args = NULL;
	result->path = NULL;
	result->index = 0;
	return (result);
}

void	add_command(t_token *list, t_command *first)
{
	t_command	*current;
	t_command	*new;

	current = first;
	new = create_command(list);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

/*void	print_command(t_command *node)
{
	int				i;
	int				j;
	t_redirection	*current;

	i = 0;
	printf("\n---- PRINT COMMANDS ----\n");
	while (node)
	{
		printf("********\n");
		printf("id : %d\n", i);
		printf("command : %s\n", node->cmd);
		printf("full command : %s\n", node->full_cmd);
		current = node->redirection;
		while (current)
		{
			printf("redirection content : %s\n", current->str);
			printf("redirection mode : %d\n", (int)current->mode);
			current = current->next;
		}
		j = 0;
		if (node->cmd)
		{
			printf("--> details of the final arguments :\n");
			while (node->args[j])
			{
				printf("--> arg %d : %s\n", j, node->args[j]);
				j++;
			}
		}
		printf("path : %s\n", node->path);
		printf("********\n");
		node = node->next;
		i++;
	}
}*/
