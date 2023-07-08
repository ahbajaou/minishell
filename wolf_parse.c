#include "minishell.h"

int	check_append(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '>';
	if (**ptr == '>')
	{
		(*ptr)++;
		tok = '+';
	}
	return (tok);
}

int	check_herdoc(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '<';
	if (**ptr == '<')
	{
		(*ptr)++;
		tok = '*';
	}
	return (tok);
}

int ft_check_chock(char *str,char *str_end,char *symbol)
{
	char	*spaces;

	spaces = " \t\r\n\f\v";
	while (str < str_end && strchr(spaces, *str))
		str++;
	return (*str && strchr(symbol, *str));
}

int ft_spaces(char *str,char *str_end,char *symbol)
{
    char *whitespaces;
    whitespaces = " \t\r\n\f\v";

    char *ptr = str;
    while (ptr < str_end && strchr(whitespaces,*ptr))
        ptr++;
    if(*ptr && strchr(symbol,*ptr))
        return(1); // Vérifier le premier caractère non-espace
    return(0);   
}

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