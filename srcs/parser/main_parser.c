#include "../../includes/minishell.h"

int main(int argc, char **argv)
{
	char *str;
	int	error;
	t_token	*list;

	(void) argc;
	str = argv[1];
	printf("str : %s\n", str);
	printf("STRNCMP : %d\n", ft_strncmp("<<", STR_D_LESS, ft_strlen("<<")));
	error = analyze_quotes(str);
	if (error)
	{
		printf("Error: Wrong number of quotes\n");
		return (0);
	}
	list = tokenization(str);
	//print_tokens(list);
	analyze_tokens_type(list);
	print_tokens(list);
	return (0);
}
