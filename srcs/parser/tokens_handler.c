/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:01:39 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 13:02:33 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, int size)
{
	t_token	*node;

	node = magic_malloc(MALLOC, sizeof(t_token), NULL);
	node->prev = NULL;
	node->next = NULL;
	node->token = magic_malloc(MALLOC, (size + 1) * sizeof(char), NULL);
	node->token[size] = '\0';
	while (size--)
		node->token[size] = str[size];
	node->type = 0;
	node->to_expand = 0;
	node->trimmed_token = NULL;
	node->expanded_token = NULL;
	return (node);
}

void	add_token(t_token *first, char *str, int size)
{
	t_token	*current;
	t_token	*new;

	current = first;
	new = create_token(str, size);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	print_tokens(t_token *node)
{
	int	i;

	i = 0;
	printf("\n\n\n---- PRINT TOKENS ----\n");
	while (node)
	{
		printf("********\n");
		printf("id : %d\n", i);
		printf("str : %s\n", node->token);
		printf("len : %d\n", (int)ft_strlen(node->token));
		printf("type : %i\n", (int)node->type);
		printf("to expand : %d\n", node->to_expand);
		printf("expanded token: %s\n", node->expanded_token);
		printf("trimmed token : %s\n", node->trimmed_token);
		printf("********\n");
		node = node->next;
		i++;
	}
}
