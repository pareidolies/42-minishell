#include "../../includes/minishell.h"

int main(int argc, char **argv)
{
	char *str;
	int	error;
	t_token	*list;

	(void) argc;
	str = argv[1];
	printf("str : %s\n", str);
	error = analyze_quotes(str);
	if (error)
	{
		printf("Error: Wrong number of quotes\n");
		return (0);
	}
	list = tokenization(str);
	print_tokens(list);
	return (0);
}
