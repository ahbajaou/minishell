/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 05:00:24 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/07 22:39:44 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_ls(char **cmd)
{
    int pid;

    if (!cmd[1])
    {
        pid = fork();
        if (pid == -1)
            return (1);
        if (pid == 0)
        {
            (void)cmd;
            char *args[] = {"ls",NULL};
            char *env[] = {NULL};
            execve("/bin/ls",args,env);
            return (0);
        }
        else
            return (0);
    }
    else
         pid = fork();
        if (pid == -1)
            return (1);
        if (pid == 0)
        {
            (void)cmd;
            char *args[] = {"ls","-l",NULL};
            char *env[] = {NULL};
            execve("/bin/ls",args,env);
            return (0);
        }
        else
            return (0);

    
}
void    execver_cmd(t_exec *cmd, ev_list *env)
{
    (void)cmd;
    (void)env;
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("ls", cmd->args[i]) == 0)
        {
            if (ft_ls(cmd->args) == 0)
                printf("ls work sucsses\n");

        }
        i++;
    }
}