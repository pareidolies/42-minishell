#include "../../includes/minishell.h"

int	analyze_quotes(char *str)
{
	int	s_quotes_nbr;
	int	d_quotes_nbr;

	int	i;

	s_quotes_nbr = 0;
	d_quotes_nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == S_QUOTE)
		{
			i++;
			s_quotes_nbr++;
			while (str[i] && str[i] != S_QUOTE)
				i++;
			if (str[i] && str[i] == S_QUOTE)
				s_quotes_nbr++;
		}
		if (str[i] && str[i] == D_QUOTE)
		{
			i++;
			d_quotes_nbr++;
			while (str[i] && str[i] != D_QUOTE)
				i++;
			if (str[i] && str[i] == D_QUOTE)
				d_quotes_nbr++;
		}
		i++;
	}
	printf("s_quote : %d\n", s_quotes_nbr);
	printf("d_quote : %d\n", d_quotes_nbr);
	if (s_quotes_nbr % 2 != 0 || d_quotes_nbr % 2 != 0)
		return (1);
	else
		return (0);
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
			i++;
			while (str[i] && str[i] != S_QUOTE)
				i++;
			printf("i : %d\n", i);
			return (i + 1);
		}
		if (str[i] == D_QUOTE)
		{
			i++;
			while (str[i] && str[i] != D_QUOTE)
				i++;
			printf("i : %d\n", i);
			return (i + 1);
		}
		else
		{
			while (str[i] && (str[i] != SPACE) && (str[i] != PIPE) && (str[i] != GREATER) && (str[i] != LESS) && (str[i] != S_QUOTE) && (str[i] != D_QUOTE))
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
		if (size == 0)
			break;
		printf("size : %d\n", size);
		if (!list)
			list = create_token(&str[i], size);
		else
		{
			add_token(list, &str[i], size);
		}
		//handling malloc error
		i += size;
	}
	return (list);
}

void	analyze_tokens_type(t_token *list)
{
	t_token	*current;

	current = list;
	while (current->next != NULL)
	{
		if (ft_strncmp(current->token, STR_LESS, ft_strlen(current->token)) == 0)
			current->type = T_LESS;
		if (ft_strncmp(current->token, STR_D_LESS, ft_strlen(current->token)) == 0)
			current->type = T_D_LESS;
		if (ft_strncmp(current->token, STR_GREATER, ft_strlen(current->token)) == 0)
			current->type = T_GREATER;
		if (ft_strncmp(current->token, STR_D_GREATER, ft_strlen(current->token)) == 0)
			current->type = T_D_GREATER;
		if (ft_strncmp(current->token, STR_PIPE, ft_strlen(current->token)) == 0)
			current->type = T_PIPE;
		else
			current->type = T_LITERAL;
		current = current->next;
	}
}