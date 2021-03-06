#include "minishell.h"

int is_builtin(char *str)
{
    if (!ft_strncmp(str, "echo", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "cd", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "pwd", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "export", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "unset", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "env", ft_strlen(str)))
        return (1);
    if (!ft_strncmp(str, "exit", ft_strlen(str)))
        return (1);
    return (0);
}

void        fill_command(t_token *list, t_command *cell, t_env *envlist)
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
        else if (current->type == T_LESS || current->type == T_GREATER || current->type == T_D_LESS || current->type == T_D_GREATER)
        {
            if (!node->redirection)
                node->redirection = create_redirection(current->next);
            else
                add_redirection(current->next, node->redirection);
        }
        current = current->next;
    }
    //printf("NODE->FULL_CMD : %s\n", node->full_cmd);
    node->args = ft_split(node->full_cmd, SPACE);
    if (is_builtin(node->cmd))
        node->path = ft_strdup("builtin");
    else
        node->path = get_command_path(node->cmd, envlist);
}

t_command   *convert_tokens_to_commands(t_token *list, t_env *envlist)
{
    t_command   *result;
    t_token     *current;

    current = list;
    result = create_command(current);
    fill_command(current, result, envlist);
    while (current->next)
    {
        if ((ft_strncmp(current->next->token, STR_PIPE, ft_strlen(current->next->token)) == 0))
        {
            add_command(current->next, result);
            fill_command(current->next->next, result, envlist);
        }
        current = current->next;
    }
    return (result);
}