#include "../../includes/minishell.h"

void    check_tokens(t_token    *list)
{
    t_token *current;

    current = list;
    while (current)
    {
        if (current->type == T_PIPE && !current->next)
        {
            printf("error: pipe and nothing after\n");
            exit(1); //faire une sortie propre ;)
        }
        if (current->type == T_PIPE && current->next->type == T_PIPE)
        {
            printf("error: two or more pipes in a row!\n");
            exit(1); //idem
        }
        if ((current->type == T_LESS || current->type == T_D_LESS
            || current->type == T_GREATER || current->type == T_D_GREATER) 
            && !current->next)
        {
            printf("error: redirection and nothing after\n");
            exit(1); //idem
        }
        if ((current->type == T_LESS || current->type == T_D_LESS
            || current->type == T_GREATER || current->type == T_D_GREATER) 
            && current->next->type == T_PIPE)
        {
            printf("error: redirection and a pipe after\n");
            exit(1); //idem
        }
        if ((current->type == T_LESS || current->type == T_D_LESS
            || current->type == T_GREATER || current->type == T_D_GREATER) 
            && (current->next->type == T_LESS || current->next->type == T_D_LESS
            || current->next->type == T_GREATER || current->next->type == T_D_GREATER))
        {
            printf("error: two or more redirections in a row\n");
            exit(1); //idem
        }
        current = current->next;
    }
}
