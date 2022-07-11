#include "../../includes/minishell.h"

t_token *create_token(char *str, int flag)
{
    t_token node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->prev = NULL;
    node->next = NULL;
    node->token = str;
    node->flag = flag;
    return (node);
}

t_token *add_token(t_token *list, char *str, int flag)
{
    t_token *current;
    t_token *node;
    int     i;

    current = list;
    node = create_token(str, flag);
    if (list == NULL)
        return (node);
    while (current->next != NULL)
        current = current->next;
    current->next = node;
    node->next = NULL;
    return (list);
}

void    print_tokens(t_token *token)
{
    int i;

    i = 0;
    while (token)
    {
        printf("********\n");
        printf("id : %d\n");
        printf("str : %s\n");
        printf("flag : %i\n");
        printf("********\n");
        token = token->next;
        i++;
    }
}