#include "../../includes/minishell.h"

void main_parser(char *str, t_env *envlist)
{
	int	error;
	t_token	*list;
	t_command	*command;
	char	*env;

	env = ft_getenv(str, envlist);
	printf("ENV : %s\n", env);
	error = analyze_quotes(str);
	if (error)
	{
		printf("Error: Wrong number of quotes\n");
		return;
	}
	list = tokenization(str);
	//print_tokens(list);
	analyze_tokens_type(list);
	analyze_literals_type(list);
	analyze_tokens_to_expand(list);
	expand_tokens(list, envlist);
	trim_tokens(list);
	print_tokens(list);
	command = create_commands(list);
}
