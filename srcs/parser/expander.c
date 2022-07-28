#include "minishell.h"

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
    while (str[i] && str[i] != '$')
        i++;
    return (i);
}

int     get_expanded_token_size(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != DOLLAR && str[i] != S_QUOTE && str[i] != D_QUOTE && str[i] != SPACE)
    {
        if (str[i] == QUESTION)
            return (1);
        i++;
    }
    return (i);
}

char    *get_expanded_key(char *str, int size, t_env *envlist)
{
    //printf("substr : %s\n", ft_substr(str, 0, size));
    char    *key;
    char    *res;

    key = ft_substr(str, 0, size);
    magic_malloc(ADD, 0, key);
    res = ft_getenv(key, envlist);
    magic_malloc(FREE, 0, key);
    return(res);
}

char    *create_expanded_token(char *str, t_env *envlist)
{
    char    *result;
    int     i;
    int     size;
    int     before_dollar;
    char    *tmp;

    i = 0;
    while(str[i] && str[i] != DOLLAR)
        i++;
    result = ft_substr(str, 0, i);
    magic_malloc(ADD, 0, result);
    //printf("*result* step 1 : %s\n", result);
    while(str[i])
    {
        i++;
        size = get_expanded_token_size(&str[i]);
        //printf("size : %d\n", size);
        if (size == 0)
            break;
        tmp = ft_strjoin(result, get_expanded_key(&str[i], size, envlist));
        magic_malloc(ADD, 0, tmp);
        magic_malloc(FREE, 0, result);
        //printf("*result* step 2 : %s\n", result);
        i = i + size;
        before_dollar = get_expanded_token_start(&str[i]);
        //printf("before dollar : %d\n", before_dollar);
        result = ft_strjoin(tmp, ft_substr(&str[i], 0, before_dollar));
        magic_malloc(ADD, 0, result);
        magic_malloc(FREE, 0, tmp);
        //printf("*result* step 3 : %s\n", result);
        i = i + before_dollar;
    }
    return (result);
}

void    expand_tokens(t_token *list, t_env *envlist)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        //if (current->to_expand)
            current->expanded_token = create_expanded_token(current->token, envlist);
        //else
        //    current->expanded_token = current->token;
        current = current->next;
    }
}
