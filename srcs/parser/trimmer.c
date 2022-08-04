#include "minishell.h"

char    *withdraw_quotes(char   *str)
{
    int     i;
    char    *result;
    int     start;
    char    *tmp;
    char    *substring;

    //printf("STR : %s\n", str);
    tmp = ft_strdup("");
    magic_malloc(ADD, 0, tmp);
    i = 0;
    while (str[i])
    {
        start = i;
        if (str[i] == S_QUOTE)
        {
            i++;
            while(str[i] && str[i] != S_QUOTE)
                i++;
            substring = ft_substr(str, start + 1, i - start - 1);
            magic_malloc(ADD, 0, substring);
            result = ft_strjoin(tmp, substring);
            magic_malloc(ADD, 0, result);
            magic_malloc(FREE, 0, substring);
            //printf("\n\nRES 1 : %s\n", result);
            magic_malloc(FREE, 0, tmp);
            i++;
        }
        else if (str[i] == D_QUOTE)
        {
            i++;
            while(str[i] && str[i] != D_QUOTE)
                i++;
            substring = ft_substr(str, start + 1, i - start - 1);
            magic_malloc(ADD, 0, substring);
            result = ft_strjoin(tmp, substring);
            magic_malloc(ADD, 0, result);
            magic_malloc(FREE, 0, substring);
            //printf("\n\nRES 2 : %s\n", result);
            magic_malloc(FREE, 0, tmp);
            i++;
        }
        else
        {
            while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
                i++;
            substring = ft_substr(str, start, i - start);
            magic_malloc(ADD, 0, substring);
            result = ft_strjoin(tmp, substring);
            magic_malloc(ADD, 0, result);
            //printf("\n\nRES 3 : %s\n", result);
            magic_malloc(FREE, 0, substring);
            magic_malloc(FREE, 0, tmp);
        }
        tmp = ft_strdup(result);
        magic_malloc(ADD, 0, tmp);
        magic_malloc(FREE, 0, result);
        //i++;
    }
    result = ft_strdup(tmp);
    //magic_malloc(ADD, 0, result);
    magic_malloc(FREE, 0, tmp);
    //printf("\n\nFINAL RESULT : %s\n", result);
    return (result);
}

/*char    *withdraw_quotes(char   *str)
{
    int     i;
    char    *result;
    int     start;

    //printf("STR : %s\n", str);
    result = ft_strdup("");
    i = 0;
    while (str[i])
    {
        start = i;
        if (str[i] == S_QUOTE)
        {
            i++;
            while(str[i] && str[i] != S_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start + 1, i - start - 1));
            //printf("RES 1 : %s\n", result);
            i++;
        }
        else if (str[i] == D_QUOTE)
        {
            i++;
            while(str[i] && str[i] != D_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start + 1, i - start - 1));
            //printf("RES 2 : %s\n", result);
            i++;
        }
        else
        {
            while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start, i - start));
            //printf("RES 3 : %s\n", result);
        }
        //i++;
    }
    return (result);
}*/

/*void    trim_commands(t_command *list)
{
    t_command *current;
    int i;

    current = list;
    while (current != NULL)
    {
        current->trimmed_token = withdraw_quotes(current->expanded_token);
        current = current->next;
    }
}*/