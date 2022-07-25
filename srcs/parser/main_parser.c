#include "minishell.h"

t_command *main_parser(char *str, t_env *envlist)
{
	int	error;
	t_token	*list;
	t_command	*command;
	char	*env;

	env = ft_getenv(str, envlist);
	//printf("ENV : %s\n", env);
	error = analyze_quotes(str);
	if (error)
	{
		printf("Error: Wrong number of quotes\n");
		return(NULL);
	}
	list = tokenization(str);
	//print_tokens(list);
	analyze_tokens_type(list);
	check_tokens(list);
	analyze_literals_type(list);
	analyze_tokens_to_expand(list);
	expand_tokens(list, envlist);
	trim_tokens(list);
	print_tokens(list);
	command = convert_tokens_to_commands(list, envlist);
	print_command(command);
	return (command);
}
