#include "../../includes/minishell.h"

void main_parser(char *str)
{
	int	error;
	t_token	*list;
	t_commande	*command;

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
	//expand_tokens
	trim_tokens(list);
	print_tokens(list);
	command = create_commands(list);
}
