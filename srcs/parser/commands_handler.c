#include "../../includes/minishell.h"

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
    result->path = NULL;
    result->options = NULL;
    result->parameters = NULL;
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
        /*printf("path : %s\n", node->path);
        printf("options : XX\n");
        printf("parameters : XX\n");
        printf(" redirections : XX\n");*/
        printf("********\n");
        node = node->next;
        i++;
    }
}
