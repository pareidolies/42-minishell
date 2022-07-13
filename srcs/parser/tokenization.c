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

int	get_token_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == PIPE)
			return (1);
		if (str[i + 1])
		{
			if ((str[i] == LESS && str[i + 1] == LESS)
				|| (str[i] == GREATER && str[i + 1] == GREATER))
				return (2);
		}
		if (str[i] == LESS || str[i] == GREATER)
			return (1);
		if (str[i] == S_QUOTE)
		{
			while (str[i] && str[i] != S_QUOTE)
				i++;
		}
		else if (str[i] == D_QUOTE)
		{
			while (str[i] && str[i] != D_QUOTE)
				i++;
		}
		else
		{
			while (str[i] && (str[i] != SPACE) && (str[i] != PIPE) && (str[i] != GREATER) && (str[i] != LESS))
				i++;
			return (i);
		}
	}
	return (0);
}

t_token	*tokenization(char *str)
{
	t_token	*list;
	int		i;
	int		size;

	if (!str)
		return (NULL);
	list = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		size = get_token_size(&str[i]);
		printf("size : %d\n", size);
		if (!list)
			list = create_token(&str[i], size);
		else
		{
			add_token(list, &str[i], size);
			printf("hello\n");
		}
		//handling malloc error
		i += size;
	}
	return (list);
}
