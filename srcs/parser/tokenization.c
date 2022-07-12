#include "../../includes/minishell.h"

int	analyze_quotes(char *str)
{
	int	error;
	int	s_quotes_nbr;
	int	d_quotes_nbr;
	int	i;

	s_quotes_nbr = 0;
	d_quotes_nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quotes_nbr++;
		if (str[i] == '\"')
			d_quotes_nbr++;
		i++;
	}
	if (s_quotes_nbr % 2 != 0 || d_quotes_nbr % 2 != 0)
		error = 1;
	else
		error = 0;
	return (error);
}
