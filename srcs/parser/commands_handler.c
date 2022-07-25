#include "minishell.h"

t_command *create_command(t_token *list)
{
    t_command   *result;
    t_token     *current;
    
    result = malloc(sizeof(t_command));
    if (!result)
        return (NULL);
    current = list;
    while (current->next && current->type != T_LITERAL)
        current = current->next;
    current->type = T_CMD;
    result->prev = NULL;
    result->next = NULL;
    result->cmd = ft_strdup(current->trimmed_token);
    if (!(result->cmd))
		return (NULL);
    result->redirection = NULL;
    result->path = NULL;
    return (result);
}

void    add_command(t_token *list, t_command *first)
{
    t_command   *current;
    t_command   *new;

    current = first;
    new = create_command(list);
    while (current->next != NULL)
       current = current->next;
    current->next = new;
    new->prev = current;
}

void    print_command(t_command *node)
{
    int i;
    i = 0;

    printf("---- PRINT COMMANDS ----\n");
    while (node)
    {
        printf("********\n");
        printf("id : %d\n", i);
        printf("command : %s\n", node->cmd);
        printf("full command : %s\n", node->full_cmd);
        if (node->redirection)
            printf("redirection : %s\n", node->redirection->str);
        /*printf("path : %s\n", node->path);
        printf("options : XX\n");
        printf("parameters : XX\n");
        printf(" redirections : XX\n");*/
        printf("********\n");
        node = node->next;
        i++;
    }
}
