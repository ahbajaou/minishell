#include "minishell.h"

int	check_symbol(char *str, char *stre, char *symbol)
{
	if (!str)
		return (0);
	while (str < stre && !strchr(symbol, *str))
		str++;
	return (str < stre && strchr(symbol, *str));
}

int	is_symbol(char *str, char *stre, char *symbol)
{
	char	*spaces;

	spaces = " \t\r\n\f\v";
	while (str < stre && strchr(spaces, *str))
		str++;
	return (*str && strchr(symbol, *str));
}

int	len_str(char *str, char *end)
{
	int	len;

	len = 0;
	while (&str[len] < end)
		len++;
	return (len);
}

char	*ret_str(char *str, char *end)
{
	char	*f_str;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (!end)
		return (str);
	f_str = (char *)malloc(sizeof(char) * (len_str(str, end) + 1));
	while (str < end)
	{
		f_str[i++] = *str;
		str++;
	}
	f_str[i] = '\0';
	return (f_str);
}

// int main() 
// {
//     char input[] = "cmd1 | cmd2 >> output.txt";
//     char *ptr = input;
//     char *end = input + sizeof(input) - 1;
//     char *previous = NULL;
//     char *ep = NULL;

//     printf("Input: %s\n", input);

//     while(1) 
// 	{
//         int tok = get_token(&ptr, end, &previous, &ep);
//         if (tok == 0) 
//             break;
	
//         char *token_str = ret_str(previous, ep);
//         printf("Token: %s\n", token_str);
//         free(token_str);
//     }
//     return 0;
// }
