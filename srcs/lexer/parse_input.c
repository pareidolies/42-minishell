/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:57:38 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/11 18:20:59 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input2(t_token *tokens, t_env *envlist)
{
	t_command	*commands;

	analyze_literals_type(tokens);
	analyze_export(tokens);
	expander(tokens, envlist);
	commands = convert_tokens_to_commands(tokens, envlist);
	print_command(commands);
	free_tokens(tokens);
	return (commands);
}

t_command	*parse_input(char *str, t_env *envlist)
{
	t_token		*tokens;
	t_command	*commands;

	if (!str[0])
		return (NULL);
	if (check_quotes(str))
	{
		g_exit_status = 2;
		return (NULL);
	}
	tokens = convert_input_to_tokens(str);
	if (analyze_tokens_type(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (check_tokens(tokens))
	{
		free_tokens(tokens);
		g_exit_status = 2;
		return (NULL);
	}
	commands = parse_input2(tokens, envlist);
	return (commands);
}
