#include "minishell.h"

t_redirection *create_redirection(t_token *list)
{
    t_redirection   *result;
    t_token         *current;
    
    result = malloc(sizeof(t_redirection));
    if (!result)
        return (NULL);
    current = list;
    result->prev = NULL;
    result->next = NULL;
    if (current->type == T_INPUT)
        result->mode = INFILE;
    else if (current->type == T_OUTPUT)
        result->mode = TRUNC;
    else if (current->type == T_DELIMITER)
        result->mode = DELIMITER;
    else if (current->type == T_APPEND)
        result->mode = APPEND;
    result->str = ft_strdup(current->trimmed_token);
    if (!(result->str))
		return (NULL);
    result->fd = -1;
    return (result);
}

void    add_redirection(t_token *list, t_redirection *first)
{
    t_redirection   *current;
    t_redirection   *new;

    current = first;
    new = create_redirection(list);
    while (current->next != NULL)
       current = current->next;
    current->next = new;
    new->prev = current;
}