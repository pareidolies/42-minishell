#include "minishell.h"

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
			if (str[i + 1] && str[i + 1] != LESS && str[i + 1] != GREATER && str[i + 1] != PIPE)
				return (i + 1 + get_token_size(&str[i + 1]));
			else
				return (i + 1);
		}
		if (str[i] == D_QUOTE)
		{
			i++;
			while (str[i] && str[i] != D_QUOTE)
				i++;
			if (str[i + 1] && str[i + 1] != LESS && str[i + 1] != GREATER && str[i + 1] != PIPE)
				return (i + 1 + get_token_size(&str[i + 1]));
			else
				return (i + 1);
		}
		else
		{
			while (str[i] && (str[i] != SPACE) && (str[i] != PIPE) && (str[i] != GREATER) && (str[i] != LESS) && (str[i] != S_QUOTE) && (str[i] != D_QUOTE))
				i++;
			if (str[i] && (str[i] == S_QUOTE || str[i] == D_QUOTE))
			{
				return (i + get_token_size(&str[i]));
			}
			else
				return (i);
		}
	}
	return (0);
}

t_token	*convert_input_to_tokens(char *str)
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
		//printf("size : %d\n", size);
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
	while (current != NULL)
	{
		if (ft_strncmp(current->token, STR_LESS, ft_strlen(current->token)) == 0)
			current->type = T_LESS;
		else if (ft_strncmp(current->token, STR_D_LESS, ft_strlen(current->token)) == 0)
			current->type = T_D_LESS;
		else if (ft_strncmp(current->token, STR_GREATER, ft_strlen(current->token)) == 0)
			current->type = T_GREATER;
		else if (ft_strncmp(current->token, STR_D_GREATER, ft_strlen(current->token)) == 0)
			current->type = T_D_GREATER;
		else if (ft_strncmp(current->token, STR_PIPE, ft_strlen(current->token)) == 0)
			current->type = T_PIPE;
		else
			current->type = T_LITERAL;
		current = current->next;
	}
}

void	analyze_literals_type(t_token *list)
{
	t_token	*current;

	current = list;
	while (current->next != NULL)
	{
		if (current->type == T_LESS && current->next->type == T_LITERAL)
			current->next->type = T_INPUT;
		else if (current->type == T_D_LESS)
			current->next->type = T_DELIMITER;
		else if (current->type == T_GREATER)
			current->next->type = T_OUTPUT;
		else if (current->type == T_D_GREATER)
			current->next->type = T_APPEND;
		current = current->next;
	}
}
