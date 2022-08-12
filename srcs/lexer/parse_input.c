/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:57:38 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 19:16:10 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input2(t_token *tokens, t_env *envlist)
{
	t_command	*commands;

	//printf("hello1\n");
	analyze_literals_type(tokens);
	// printf("hello2\n");
	analyze_export(tokens);
	// printf("hello3\n");
	expander(tokens, envlist);
	// printf("hello4\n");
	commands = convert_tokens_to_commands(tokens, envlist);
	// printf("hello5\n");
	print_command(commands);
	// printf("hello6\n");
	free_tokens(tokens);
	// printf("hello7\n");
	return (commands);
}

t_command	*parse_input(char *str, t_env *envlist)
{
	t_token		*tokens;
	t_command	*commands;

	if (!str[0])
		return (NULL);
	printf("coucou1\n");
	if (check_quotes(str))
	{
		g_exit_status = 2;
		return (NULL);
	}
	printf("coucou2\n");
	tokens = convert_input_to_tokens(str);
	printf("coucou3\n");
	if (analyze_tokens_type(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	printf("coucou4\n");
	if (check_tokens(tokens))
	{
		free_tokens(tokens);
		g_exit_status = 2;
		return (NULL);
	}
	printf("coucou5\n");
	commands = parse_input2(tokens, envlist);
	printf("coucou6\n");
	return (commands);
}
