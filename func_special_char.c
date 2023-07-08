#include "minishell.h"

char    find_sym(char *str,char *stre)
{
    while (str < stre)
    {
        if (strchr("\"'$", *str))
            return (*strchr("\"'$",*str));
        str++;
    }
    return(0);
}

char    *substr_ing(char **str, char sym)
{
    char *location_sym = strchr(*str,sym);
    while(*str < location_sym)
    {
        char *extracted = substring_copy(*str,location_sym);
        *str = location_sym;
        return extracted;
    }
    return(NULL);
}

char *extract_substring(char **str,char symbol,t_copy *env)
{
    if(symbol == '"' || symbol == '\'')
        return h_quotes(str,symbol,env);
    if(symbol == '$')
        return h_dollar(str,env);
    return NULL;
}

void	concatenate_remaining_strings(char *str, char *stre, char **new, char *join)
{
	if (join)
	{
		*new = join;
		free_s1_s2(join);
	}
	if (str < stre)
		*new = ft_strjoin__just1_free(*new, str);
}