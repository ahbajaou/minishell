/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:18:09 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/20 00:43:02 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	count_wd(char *str, char sep)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (str[i])
	{
		if ((str[i] != sep && str[i + 1] == sep)
			|| (str[i] != sep && str[i + 1] == '\0'))
			wd++;
		i++;
	}
	return (wd);
}

char	**count_char(char **spl, char *str, char sep, int wd)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] && str[i] == sep)
			i++;
		len = 0;
		while (str[i] && str[i] != sep)
		{
			i++;
			len++;
		}
		spl[j++] = (char *)malloc(sizeof(char *) * len);
	}
	return (spl);
}

char	**stock_spl(char **spl, char *str, char sep, int wd)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] && str[i] == sep)
			i++;
		len = 0;
		while (str[i] && str[i] != sep)
		{
			spl[j][len] = str[i];
			i++;
			len++;
		}
		spl[j++][len] = '\0';
	}
	return (spl);
}

char	**ft_split(char *str, char sep)
{
	char	**spl;
	int		wd;

	wd = 0;
	wd = count_wd(str, sep);
	spl = (char **)malloc(sizeof(char *) * wd + 1);
	if (!spl)
		return (NULL);
	spl[wd] = NULL;
	spl = count_char(spl, str, sep, wd);
	spl = stock_spl(spl, str, sep, wd);
	return (spl);
}