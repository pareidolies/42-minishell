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
    while (str[i] && str[i] != '$')
        i++;
    return (i);
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

/*char    *create_expanded_token(char *str, t_env *envlist)
{
    int     size;
    int     start;
    char    *result;
    int     i;
    int     j;
    char    *before;
    char    *after;
    char    *key;
    char    *expanded_key;
    int     beginning;

    i = 0;
    j = 0;
    beginning = 0;
    while (str[i] && there_is_a_dollar(&str[i]))
    {
        start = get_expanded_token_start(&str[i]);
        size = get_expanded_token_size(&str[i]);
        printf("start : %d / size = %d\n", start, size);
        key = ft_substr(&str[i], start, size);
        printf("key : %s\n", key);
        expanded_key = ft_getenv(ft_substr(&str[i], start, size), envlist);
        if (beginning == 0)
        {
            before = ft_substr(&str[i], 0, start - 1);
            beginning = 42;
            printf("beginning = 0");
        }
        else if (beginning == 42)
        {
            before = ft_strdup(result);
            printf("beginning = 1");
        }
        printf("before : %s\n", before);
        after = ft_substr(&str[i], start + size, ft_strlen(&str[i]) - start - size);
        result = ft_strjoin(before, expanded_key);
        result = ft_strjoin(result, after);
        printf("result : %s\n", result);
        free(key);
        free(expanded_key);
        free(before);
        free(after);
        i = i + start + size;
    }
    return (result);
}*/

char    *get_expanded_key(char *str, int size, t_env *envlist)
{
    printf("substr : %s\n", ft_substr(str, 0, size));
    return(ft_getenv(ft_substr(str, 0, size), envlist));    
}

char    *create_expanded_token(char *str, t_env *envlist)
{
    char    *result;
    int     i;
    int     size;
    int     before_dollar;

    (void) envlist;
    i = 0;
    while(str[i] && str[i] != DOLLAR)
        i++;
    result = ft_substr(str, 0, i);
    printf("*result* step 1 : %s\n", result);
    //while(str[i])
    //{
        i++;
        size = get_expanded_token_size(&str[i]);
        result = ft_strjoin(result, get_expanded_key(&str[i], size, envlist));
        printf("*result* step 2 : %s\n", result);
        i = i + size;
        before_dollar = get_expanded_token_start(&str[i]);
        //result = ft_strjoin(result, ft_substr(&str[i], 0, before_dollar));
        //printf("*result* step 3 : %s\n", result);
        //i = i + before_dollar;
    //}
    return (result);
}

void    expand_tokens(t_token *list, t_env *envlist)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        if (current->to_expand)
            current->expanded_token = create_expanded_token(current->token, envlist);
        else
            current->expanded_token = current->token;
        current = current->next;
    }
}
