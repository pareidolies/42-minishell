#include "minishell.h"

void    free_tokens(t_token *list)
{
    t_token *current;

    current = list;
    while (current)
    {
        free(current->token);
        current->token = NULL;
        free(current->trimmed_token);
        current->trimmed_token = NULL;
        if (current->expanded_token)
        {
            free(current->expanded_token);
            current->expanded_token = NULL;
        }
        current = current->next;
    }
}
