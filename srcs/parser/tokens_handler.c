#include "../../includes/minishell.h"

t_token *create_token(char *str, int size)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->prev = NULL;
    node->next = NULL;
    node->token = malloc((size + 1) * sizeof(char));
    if (!(node->token))
		return (NULL);
	node->token[size] = '\0';
	while (size--)
		node->token[size] = str[size];
    node->type = 0;
    return (node);
}

void    add_token(t_token *first, char *str, int size)
{
    t_token *current;
    t_token *new;

    current = first;
    new = create_token(str, size);
    while (current->next != NULL)
       current = current->next;
    current->next = new;
    new->prev = current;
}

void    print_tokens(t_token *node)
{
    int i;
    i = 0;

    printf("---- PRINT TOKENS ----\n");
    while (node)
    {
        printf("********\n");
        printf("id : %d\n", i);
        printf("str : %s\n", node->token);
        printf("type : %i\n", (int)node->type);
        printf("********\n");
        node = node->next;
        i++;
    }
}
