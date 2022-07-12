#include "../../includes/minishell.h"

t_token *create_token(char *str, int flag)
{
    t_token *node;

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

void    print_tokens(t_token *node)
{
    int i;

    i = 0;
    while (node)
    {
        printf("********\n");
        printf("id : %d\n", i);
        printf("str : %s\n", node->token);
        printf("flag : %i\n", node->flag);
        printf("********\n");
        node = node->next;
        i++;
    }
}
