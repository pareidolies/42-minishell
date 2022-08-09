/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:57:38 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 12:57:45 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(char *str, t_env *envlist)
{
	t_token		*tokens;
	t_command	*commands;

	if (!str[0])
		return (NULL);
	if (check_quotes(str))
		return (NULL);
	tokens = convert_input_to_tokens(str);
	if (analyze_tokens_type(tokens))
		return (NULL);
	if (check_tokens(tokens))
		return (NULL);
	analyze_literals_type(tokens);
	expander(tokens, envlist);
	commands = convert_tokens_to_commands(tokens, envlist);
	free_tokens(tokens);
	//print_command(commands);
	return (commands);
}
