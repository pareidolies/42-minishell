#include "minishell.h"

t_command *parse_input(char *str, t_env *envlist)
{
	t_token	*tokens;
	t_command	*commands;

	if (check_quotes(str))
		return(NULL);
	tokens = convert_input_to_tokens(str);
	//print_tokens(list);
	analyze_tokens_type(tokens);
	if (check_tokens(tokens))
		return (NULL);
	analyze_literals_type(tokens);
	expander(tokens, envlist);
	//trim_tokens(list);
	//print_tokens(list);
	commands = convert_tokens_to_commands(tokens, envlist);
	free_tokens(tokens);
	print_command(commands);
	return (commands);
}

