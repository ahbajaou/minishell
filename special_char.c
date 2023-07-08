#include "minishell.h"
char    *check_special(char *str,t_copy *env)
{
    char *end = str + strlen(str);

    if (check_for_symbol(str, end, "\"'$"))
    {
        char *processed_str = handle_quotes_and_dollar(str, env);
        free(str);
        return processed_str;
    }
    return str;
}

char    *handle_quotes_and_dollar(char *str,t_copy *env)
{
    char symbol;
    char *sym_loc;
    char *joinstr;
    char *newstr;
    char *end = str + strlen(str);
    char *processed_str = NULL;

    
    while (check_for_symbol(str,end,"\"'$"))
    {
        symbol =  find_sym(str,end);
        sym_loc = substr_ing(&str,symbol);
        newstr =  extract_substring(&str,symbol,env);
        newstr =  ft_strjoin_allfree(sym_loc,newstr);
        joinstr = ft_strjoin__just1_free(joinstr,newstr);
    }
        concatenate_remaining_strings(str,end,&newstr,joinstr);
        processed_str = ft_strdup(newstr);
        free(joinstr);

    return(processed_str);
}

char	*ft_strjoin_allfree(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free_s1_s2(s2);
	free_s1_s2(s1);
	return (str);
}
char	*ft_strjoin__just1_free(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (s2)
	{
		while (*s2)
			str[i++] = *(s2++);
		str[i] = '\0';
	}
	if (*s1)
		free(s1);
	return (str);
}

void	free_s1_s2(char *str)
{
	if (str && *str)
		free(str);
}
char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc (sizeof(char) * (strlen((char *)s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}