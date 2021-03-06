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
    int j;

    i = 0;
    t_redirection *current;

    printf("\n\n\n---- PRINT COMMANDS ----\n");
    while (node)
    {
        printf("********\n");
        printf("id : %d\n", i);
        printf("command : %s\n", node->cmd);
        printf("full command : %s\n", node->full_cmd);
        current = node->redirection;
        while (current)
        {
            printf("redirection content : %s\n", current->str);
            printf("redirection mode : %d\n", (int)current->mode);
            current = current->next;
        }
        j = 0;
        printf("--> details of the final arguments :\n");
        while (node->args[j])
        {
            printf("--> arg %d : %s\n", j, node->args[j]);
            j++;
        }
        printf("path : %s\n", node->path);
        /*printf("options : XX\n");
        printf("parameters : XX\n");
        printf(" redirections : XX\n");*/
        printf("********\n");
        node = node->next;
        i++;
    }
}
