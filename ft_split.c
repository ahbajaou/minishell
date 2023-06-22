/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:18:09 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/22 04:43:31 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int	count_wd(char *str, char sep)
// {
// 	int	i;
// 	int	wd;

// 	i = 0;
// 	wd = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] != sep && str[i + 1] == sep)
// 			|| (str[i] != sep && str[i + 1] == '\0'))
// 			wd++;
// 		i++;
// 	}
// 	return (wd);
// }

// char	**count_char(char **spl, char *str, char sep, int wd)
// {
// 	int	i;
// 	int	len;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && j < wd)
// 	{
// 		while (str[i] && str[i] == sep)
// 			i++;
// 		len = 0;
// 		while (str[i] && str[i] != sep)
// 		{
// 			i++;
// 			len++;
// 		}
// 		spl[j++] = (char *)malloc(sizeof(char *) * len);
// 	}
// 	return (spl);
// }

// char	**stock_spl(char **spl, char *str, char sep, int wd)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && j < wd)
// 	{
// 		while (str[i] && str[i] == sep)
// 			i++;
// 		len = 0;
// 		while (str[i] && str[i] != sep)
// 		{
// 			spl[j][len] = str[i];
// 			i++;
// 			len++;
// 		}
// 		spl[j++][len] = '\0';
// 	}
// 	return (spl);
// }

// char	**ft_split(char *str, char sep)
// {
// 	char	**spl;
// 	int		wd;

// 	wd = 0;
// 	// printf(">>%s<<\n",str);
// 	wd = count_wd(str, sep);
// 	spl = (char **)malloc(sizeof(char *) * wd + 1);
// 	if (!spl)
// 		return (NULL);
// 	// spl[wd] = NULL;
// 	// printf("--split---\n");
// 	spl = count_char(spl, str, sep, wd);
// 	spl = stock_spl(spl, str, sep, wd);
// 	// printf("loop\n");
// 	return (spl);
// }
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;

	i = 0;
	if (start > ft_strlen((char *)s))
		len = 0;
	while (i < len && s[i])
		i++;
	new = malloc (i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

int	count_c(const char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		count++;
		i++;
	}
	return (count);
}

int	count_word(const char *str, char c)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] == c)
			|| (str[i] != c && str[i + 1] == '\0'))
			wd++;
		i++;
	}
	return (wd);
}

char	**ft_split( char *s, char c)
{
	int		i;
	int		sp;
	int		xc;
	char	**spl;
	int		x;

	sp = 0;
	i = 0;
	// printf("---split----\n");
	xc = count_word(s, c);
	spl = malloc(sizeof(char *) * (xc + 1));
	if (!spl)
		return (NULL);
	while (i < xc)
	{
		while (s[sp] && s[sp] == c)
			sp++;
		x = count_c(s, c, sp);
		spl[i] = ft_substr(s, sp, x);
		sp += x + 1;
		i++;
	}
	spl[i] = NULL;
	return (spl);
}