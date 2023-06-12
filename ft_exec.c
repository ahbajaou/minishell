/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:18 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/12 01:08:08 by ahbajaou         ###   ########.fr       */
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
void    get_pwd(void)
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n",cwd);
}

void    change_dr(char **str)
{
    (void)str;
    char oldpwd[256];
    char pwd[256];
    if (getcwd(oldpwd, sizeof(oldpwd)) != NULL)
        printf("----%s\n",oldpwd);
     if (strcmp(str[0], "cd") == 0)
        chdir("..");
     else if (strcmp(str[0], "cd") == 0 && strcmp(str[1], "..") == 0)
             chdir("..");
     if (getcwd(pwd, sizeof(pwd)) != NULL)
        printf("----%s\n",pwd);
}
void    ft_exec(t_exec *cmd)
{
    if (strcmp("echo", cmd->args[0]) == 0 && strcmp("-n", cmd->args[1]) == 0)
        echo(cmd->args);
    else if (strcmp("echo", cmd->args[0]) == 0)
        echonew(cmd->args);
    else if (strcmp("pwd", cmd->args[0]) == 0)
        get_pwd();
    else if (strcmp("cd", cmd->args[0]) == 0)
        change_dr(cmd->args);
    // printf("%s\n",cmd->args[1]);
}