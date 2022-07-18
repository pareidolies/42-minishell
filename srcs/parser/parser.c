#include "../../includes/minishell.h"

void        fill_command(t_token *list)
{
    t_token *current;

    current = list;

    while (current && current->type != T_LITERAL)
    {

    }
    while (current)
    {
        if (ft_strncmp(current->token, STR_PIPE, ft_strlen(current->token)) == 0)
            break;
        else if (is_redirection(current->token))
            create_redirection(current);
        else
            add_command(current->token)
    }
}

t_command   *convert_tokens_to_commands(t_token *list)
{
    t_command   *result;
    t_token     *current;

    current = list;
    while (current)
    {
        if ((ft_strncmp(current->token, STR_PIPE, ft_strlen(current->token)) == 0) && current->next)
        {
            result = create_command(current->next);
            fill_command(current->next, result);
        }
        else if ((ft_strncmp(current->token, STR_PIPE, ft_strlen(current->token)) == 0) && !current->next)
        {
            printf("error: pipe and nothing after");
            exit (1);
        }
        else
            current = current->next;
    }
    return (result);
}
