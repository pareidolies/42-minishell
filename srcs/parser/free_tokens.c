#include "minishell.h"

void    free_redirections(t_redirection *list)
{
    t_redirection *current;
    t_redirection *tmp;

    current = list;
    while (current)
    {
        magic_malloc(FREE, 0, current->str);
        tmp = current->next;
        magic_malloc(FREE, 0, current);
        current = tmp;
    }
}

void    free_commands(t_command *list)
{
    t_command *current;
    t_command *tmp;
    int i;

    current = list;
    while (current)
    {
        magic_malloc(FREE, 0, current->cmd);
        magic_malloc(FREE, 0, current->full_cmd);
        magic_malloc(FREE, 0, current->path);
        i = 0;
        while(current->args[i])
        {
            magic_malloc(FREE, 0, current->args[i]);
            i++;
        }
        free_redirections(current->redirection);
        tmp = current->next;
        current = tmp;
    }
}

void    free_tokens(t_token *list)
{
    t_token *current;
    t_token *tmp;

    current = list;
    while (current)
    {
        magic_malloc(FREE, 0, current->token);
        magic_malloc(FREE, 0, current->trimmed_token);
        magic_malloc(FREE, 0, current->expanded_token);
        tmp = current->next;
        magic_malloc(FREE, 0, current);
        current = tmp;
    }
}
