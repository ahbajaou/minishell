#include "minishell.h"
void	check_free(char *str)
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
char	*ft_strjoin5(char *s1, char *s2)
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
	check_free(s2);
	check_free(s1);
	return (str);
}
char	*ft_strjoin2(char *s1, char *s2)
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
