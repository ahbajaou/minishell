/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:18 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/08 23:02:55 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    echonew(char **str)
{
    int i;

    i = 1;
    while (str[i])
        {
            printf("%s",str[i]);
            if (str[i] != '\0')
                printf(" ");
            i++;
        }
        printf("\n");
}

void    echo(char **str)
{
    int i;

    i = 2;

    while (str[i])
        {
            printf("%s",str[i]);
            if (str[i] != '\0')
                printf(" ");
            i++;
        }
    printf("\n");
}

void    ft_exec(t_exec *cmd)
{
    if (strcmp("echo", cmd->args[0]) == 0 && strcmp("-n", cmd->args[1]) == 0)
        echo(cmd->args);
    else if (strcmp("echo", cmd->args[0]) == 0)
        echonew(cmd->args);
    // printf("%s\n",cmd->args[1]);
}