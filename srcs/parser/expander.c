#include "../../includes/minishell.h"

/* If many variables to expand : ft_split ($) */

int there_is_a_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

void    analyze_tokens_to_expand(t_token *list)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        if (current->token[0] != S_QUOTE && there_is_a_dollar(current->token))
            current->to_expand = 1;
        current = current->next;
    }
}

int     get_expanded_token_start(char *str)
{
    int i;

    i = 0;
    while (str[i] != '$')
        i++;
    return (i + 1);
}

int     get_expanded_token_size(char *str)
{
    int i;
    int start;

    i = 0;
    while (str[i] && str[i] != '$')
        i++;
    start = i;
    while (str[i] && str[i] != SPACE && str[i] != S_QUOTE && str[i] != D_QUOTE)
        i++;
    return (i - start - 1);
}

char    *create_expanded_token(char *str)
{
    char    *result;
    int     i;
    char    *before;
    char    *after;
    char    *key;
    char    *expanded_key;

    i = 0;
    while (there_is_a_dollar(&str[i]))
    {
        start = get_expanded_token_start(&str[i]);
        size = get_expanded_token_size(&str[i]);
        key = ft_substr(current->token, start, size);
        expanded_key = ft_getenv(key, envlist);
        before = ft_substr(current->token, 0, start - 1);
        after = ft_substr(current->token, start + size, ft_strlen(current->token) - start - size);
        current->expanded_token = ft_strjoin(before, expanded_key);
        current->expanded_token = ft_strjoin(current->expanded_token, after);
        free(key);
        free(expanded_key);
        free(before);
        free(after);
        i++;
    }
    return (result);
}

void    expand_tokens(t_token *list, t_env *envlist)
{
    t_token *current;
    int start;
    int size;
    char    *key;
    char    *expanded_key;
    char    *before;
    char    *after;

    current = list;
    while (current != NULL)
    {
        if (current->to_expand)
        {
            start = get_expanded_token_start(current->token);
            size = get_expanded_token_size(current->token);
            key = ft_substr(current->token, start, size);
            expanded_key = ft_getenv(key, envlist);
            before = ft_substr(current->token, 0, start - 1);
            after = ft_substr(current->token, start + size, ft_strlen(current->token) - start - size);
            current->expanded_token = ft_strjoin(before, expanded_key);
            current->expanded_token = ft_strjoin(current->expanded_token, after);
        }
        else
            current->expanded_token = current->token;
        current = current->next;
    }
}
