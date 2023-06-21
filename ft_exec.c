/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:17:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/21 17:28:07 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
char    *n_handel(char **str)
{
    int i;
    int j;

    i = 0;
    // printf("here\n");
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            // while (str[i][j] && str[i][j] == '-' && str[i][j + 1] == 'n' && str[i][j + 2] == 'n' &&
            //     str[i + 1][j] == '-' && str[i + 1][j + 1] == 'n' && str[i + 1][j + 2] == 'n')
            //     j++;
            // while (str[i][j] && str[i][j] == '-' && str[i][j + 1] == 'n' && str[i][j + 2] == ' ')
            //     j++;
            j++;
        }
        // printf("===%s\n",str[i]);
        i++;
    }
    return ("-n");
}
void    ft_echo(t_exec *cmd)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("echo", cmd->args[i]) == 0 && ft_strcmp("-n", cmd->args[i + 1]) != 0)
        {
            flag = 1;
            i++;
            while (cmd->args[i])
            {
                printf("%s",cmd->args[i]);
                printf(" ");
                i++;
            }
        }
        if (cmd->args[i])
        {
                
            if (ft_strcmp("echo", cmd->args[i]) == 0 && ft_strcmp("-n", n_handel(cmd->args)) == 0)
            {
                i += 2;
                while (cmd->args[i])
                {
                    printf("%s",cmd->args[i]);
                    if (!(cmd->args[i] != '\0' && cmd->args[i + 1] == '\0'))
                        printf(" ");
                    i++;
                }
            }
        }
        i++;
    }
    if (flag)
        printf("\n");
}
// void    ft_export(t_exec *cmd)
// {
//     printf("===%s\n",cmd->args[1]);
// }
void    ft_env(t_list *env2)
{

}
void    check_builting(t_exec *cmd, t_list *env)
{
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("echo", cmd->args[i]) == 0)
            ft_echo(cmd);
        // if (ft_strcmp("export", cmd->args[i]) == 0)
        //     ft_export(cmd);
        if (ft_strcmp("env", cmd->args[i]) == 0)
            ft_env(env);
        
        i++;
    }
}
void    ft_exec(t_exec *exec_cmd, t_list *envt)
{
    (void)envt;
    check_builting(exec_cmd, envt);
}