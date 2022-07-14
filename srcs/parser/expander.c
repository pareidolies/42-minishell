#include "../../includes/minishell.h"

int there_is_a_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

void    analyze_tokens_to_expand(t_token *list)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        if (current->token[0] != S_QUOTE && there_is_a_dollar(current->token))
            current->to_expand = 1;
        current = current->next;
    }
}
