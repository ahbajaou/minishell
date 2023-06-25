/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:17:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/25 01:37:24 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

#include <string.h>

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
char	*ft__strdup(char *str)
{
	int		i;
	char	*dup;

	i = strlen(str);
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
ev_list *key_value(char *key, char *value)
{
    ev_list *env;
    // printf("--keyvalaue--\n");
    env = malloc(sizeof(ev_list));
    env->key = ft__strdup(key);
    env->value = ft__strdup(value);
    env->next = NULL;
    return (env);
}
void	addback(ev_list **head, ev_list *new)
{
	ev_list	*tmp;
	tmp = *head;
	if (!head)
		*head = new;
	if (head != NULL)
	{
		if (*head == NULL)
			*head = new;
		else
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
void    print_env(ev_list *env)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (tmp->key != NULL && tmp->value != NULL)
            printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}
void    ft_env(ev_list *env, char **envp, t_exec *cmd)
{
    int i;
    int flag;

    i = 0;
    flag  = 0;

    (void)cmd;
    char **tmp;
    // if (ft_strcmp(cmd->args[0], "export") == 0)
    //     flag  = 1;
    // env = malloc(sizeof(ev_list) * 100);
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        addback(&env,key_value(tmp[0], tmp[1]));
        i++;
    }
    print_env(env);
    free(tmp);
}

void    ft_export(ev_list *env, t_exec *cmd, char **envp)
{
    ft_env(env, envp, cmd);
}
void    check_builting(t_exec *cmd, char **envp, ev_list *env)
{
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("echo", cmd->args[i]) == 0)
            ft_echo(cmd);
        if (ft_strcmp("env", cmd->args[i]) == 0)
            ft_env(env, envp, cmd);
        if (ft_strcmp("export", cmd->args[i]) == 0)
            ft_export(env, cmd, envp);
        
        i++;
    }
}

void    ft_exec(t_exec *exec_cmd, char **envp)
{
    ev_list *env = NULL;

    check_builting(exec_cmd, envp, env);
}