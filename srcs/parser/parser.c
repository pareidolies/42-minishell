#include "../../includes/minishell.h"

void        fill_command(t_token *list, t_command *cell)
{
    t_token *current;
    t_command   *node;

    node = cell;
    while (node->next != NULL)
        node = node->next;
    node->full_cmd = ft_strdup(node->cmd);
    current = list;
    while (current && current->type != T_PIPE)
    {
        if (current->type == T_LITERAL)
        {
            node->full_cmd = ft_strjoin(node->full_cmd, STR_SPACE);
            node->full_cmd = ft_strjoin(node->full_cmd, current->trimmed_token);
        }
        current = current->next;
    }
}

t_command   *convert_tokens_to_commands(t_token *list)
{
    t_command   *result;
    t_token     *current;

    current = list;
    result = create_command(current);
    fill_command(current, result);
    while (current->next)
    {
        if ((ft_strncmp(current->next->token, STR_PIPE, ft_strlen(current->next->token)) == 0))
        {
            add_command(current->next, result);
            fill_command(current->next->next, result);
        }
        current = current->next;
    }
    return (result);
}
