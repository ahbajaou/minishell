#include "minishell.h"

int	len_str(char *str, char *end)
{
	int	len;

	len = 0;
	while (&str[len] < end)
		len++;
	return (len);
}

char	*substring_copy(char *str, char *after_str)
{
	char	*f_str;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (!after_str)
		return (str);
	f_str = (char *)malloc(sizeof(char) * (len_str(str, after_str) + 1));
	while (str < after_str)
	{
		f_str[i++] = *str;
		str++;
	}
	f_str[i] = '\0';
	return (f_str);
}

