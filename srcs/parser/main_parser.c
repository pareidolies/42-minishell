#include "../../includes/minishell.h"

void main_parser(char *str)
{
	int	error;
	t_token	*list;

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
	print_tokens(list);
}
