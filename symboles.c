#include "minishell.h"

// int check_symbol(char *str, char *end, char *symbols)
// {
//     if (!str)
//         return 0;

//     while (str < end)
//     {
//         if (strchr(symbols, *str))
//             return 1;
//         str++;
//     }

//     return 0;
// }

int check_for_symbol(char *str, char *end, char *symbols)
{
    char *spaces = " \t\r\n\f\v";

    while (str < end)
    {
        if (!strchr(spaces, *str))
            break;
        str++;
    }

    return (*str && strchr(symbols, *str));
}

char    *handle_quotes_and_dollar(char *str, t_list *envList)
{
    char symbol;
    char *newStr;
    char *joinStr;
    char *s;
    char *end = str + strlen(str);
    char *processedStr = NULL;

    while (check_for_symbol(str, end, "\"'$"))
    {
        symbol = find_sym(str, end);
        s = substr_ing(&str, symbol);
        newStr = extractSubstring(&str, symbol, envList);
        newStr = ft_strjoin5(s, newStr);
        joinStr = ft_strjoin5(joinStr, newStr);
    }

    concatenate_Remaining_Strings(str, end, &newStr, joinStr);
    processedStr = ft_strdup(newStr);
    free(joinStr);

    return processedStr;
}

char* validat_String(char *str, t_list *env_list)
{
    char *end = str + strlen(str);

    if (check_for_symbol(str, end, "\"'$"))
    {
        char *processed_str = handle_quotes_and_dollar(str, env_list);
        free(str);
        return processed_str;
    }
    return str;
}

void	concatenate_Remaining_Strings(char *str, char *stre, char **new, char *join)
{
	if (join)
	{
		*new = join;
		check_free(join);
	}
	if (str < stre)
		*new = ft_strjoin2(*new, str);
}


