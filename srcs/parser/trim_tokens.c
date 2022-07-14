#include "../../includes/minishell.h"

void    trim_tokens(t_token *list)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        current->trimmed_token = ft_strtrim(current->token, "\"'");
        current = current->next;
    }
}