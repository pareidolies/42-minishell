#include "../../includes/minishell.h"

t_command *create_command(char *str, int size)
{
    t_command   *node;
    
    node = malloc(sizeof(t_command));
    if (!node)
        return (NULL);
    node->prev = NULL;
    node->next = NULL;
    node->cmd = malloc((size + 1) * sizeof(char));
    if (!(node->full_cmd))
		return (NULL);
	node->cmd[size] = '\0';
	while (size--)
		node->cmd[size] = str[size];
    node->path = NULL;
    node->options = NULL;
    node->parameters = NULL;
    node->cmd_found = 0;
    return (node);
}

void    add_command(t_token *list, t_command *first, char *str, int size)
{
    t_command   *current;
    t_command   *new;
    t_token     *token;

    token = list;
    while (token && token->type != T_LITERAL)
        token = token->next;
    token->type = T_CMD;
    current = first;
    new = create_command(token->trimmed_token, ft_strlen(token->trimmed_token));
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
        printf("path : %s\n", node->path);
        printf("options : XX\n");
        printf("parameters : XX\n");
        printf(" redirections : XX\n");
        printf("********\n");
        node = node->next;
        i++;
    }
}
