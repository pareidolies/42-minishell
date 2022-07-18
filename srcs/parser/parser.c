#include "../../includes/minishell.h"

/*void        fill_command(t_token *list)
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
}*/

t_command   *convert_tokens_to_commands(t_token *list)
{
    t_command   *result;
    t_token     *current;

    current = list;
    result = create_command(current);
    //fill_command(current);
    while (current->next)
    {
        if ((ft_strncmp(current->next->token, STR_PIPE, ft_strlen(current->next->token)) == 0))
        {
            add_command(current->next, result);
            //fill_command(current->next, result);
        }
        current = current->next;
    }
    return (result);
}
