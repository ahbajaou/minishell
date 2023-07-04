/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:17:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/04 03:01:14 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
int    handel_q(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (str[i])
    {
        printf("--%c--\n",str[i]);
         if (str[i] && str[i] == '-' && str[i + 1] == 'n')
         {
            flag  = 1;
            break ;
         }
         else
            flag = 0;

        //  if (str[i] && str[i] == 'n' && str[i + 1] == 'n')
        //  {
        //     flag  = 1;
        //     break ;
        //  }
        i++;
    }
    if (flag == 1)
        return (0);
    return (1);
}
void    echo_handler(char **args)
{
    int i;
    // int j = 0;
    int flag;

    i = 1;
    flag = 0;
     while (args[i])
     {
            // j = 0;
            // while  (args[i][j])
            // {
            //     // if (!( args[i][j] == '-' && args[i][j + 1] == 'n') || !(args[i][j] == 'n' && args[i][j + 1] == 'n'))
            //     // {
            //     //     printf("--break--\n");
            //     //     break ;
            //     // }
            //     if (args[i][j] == '-')
            //     {
            //         while (args[i][j] == 'n')
            //         {
            //              printf("%c",args[i][j]);
            //             j++;
            //         }
            //     }
            //     // while ( args[i][j] == 'n' && args[i][j + 1] == 'n')
            //     //     j++;
            //     j++;
            // }
            if (ft_strcmp(args[i], "-n") != 0 && handel_q(args[i]) == 1)
            {
                while (args[i])
                {
                    printf("%s",args[i]); 
                    if (args[i + 1] == NULL)
                        break ;
                    printf("[+]");
                    i++;
                }
                return ;
            }
        i++;
     }   
}
void ft_echo(t_exec *cmd, ev_list *env)
{
    int i;
    // int j = 0;
    int flag;

    i = 0;
    flag = 0;
     (void)env;
     while (cmd->args[i])
     {
        if (ft_strcmp(cmd->args[i], "echo") == 0 && ft_strcmp(cmd->args[i + 1], "-n") == 0)
        {
            echo_handler(cmd->args);
            break ;
        }
        // if (ft_strcmp(cmd->args[i], "echo") == 0 && ft_strcmp(cmd->args[i + 1], "-n") != 0)
        // {

        // }
        i++;
     }
}
char *ft__strdup(char *str)
{
    int i;
    char *dup;

    if (!str)
        return (NULL);
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
    env = malloc(sizeof(ev_list));
    env->key = ft__strdup(key);
    env->value = ft__strdup(value);
    env->next = NULL;
    return (env);
}

void addback(ev_list **list, ev_list *new)
{
    ev_list *tmp;

    tmp = *list;
    if (!(*list))
    {
        *list = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}
int is_alpha(char **str)
{
    int i;
    int j;

    i = 1;
    if (!*str || !str)
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if ((str[i][j] >= 'a' && str[i][j] <= 'z') || (str[i][j] >= 'A' && str[i][j] <= 'Z'))
            {
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
int _isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}
int str_chr(char **str)
{
    int i;
    int j;

    i = 1;
    if (!*str || !str)
        return (0);
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (str[i][j] == '=')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}
void print_env(ev_list *env, int flag)
{
    ev_list *tmp;

    tmp = env;
    (void)flag;

    while (tmp)
    {
        if (flag == 1 && tmp->key != NULL && tmp->value == NULL)
            printf("declare -x %s\n", tmp->key);
        if (flag == 0 && tmp->key != NULL && tmp->value != NULL)
            printf("%s=%s\n", tmp->key, tmp->value);
        if (flag == 1 && tmp->key != NULL && tmp->value != NULL)
            printf("declare -x %s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    free(tmp);
}

void delet_expo(ev_list *env, char *key,char *value)
{
    ev_list *tmp;

    tmp = env;
    (void)value;
    ev_list *perv;
            if (env != NULL)
            {
                if (tmp->key != key)
                {
                    while (tmp->next != NULL)
                    {
                    // printf("========%s=====\n",tmp->key);
                        if (ft_strcmp(tmp->next->key, key) == 0)
                        {

                            perv = tmp->next;
                            tmp->next = tmp->next->next;
                            free(perv);
                            return ;
                         }
                        tmp = tmp->next;
                    }
                }
            }

}
int check_double(ev_list *env, char *key, char *value)
{
    (void)env;
    (void)value;

    ev_list *tmp;
    tmp = env;
    while (tmp)
    {
            if (key != NULL && value == NULL)
                return (0);
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value))
        {
            delet_expo(env, key, value);
            addback(&env, key_value(key, value));
            return (0);
        }
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
            return (0);
        if (ft_strcmp(tmp->key, key) == 0 && value == NULL)
            return (0);
        tmp = tmp->next;
    }
    return (1);
}
void expo_pars(char *str,char *str1,ev_list *env)
{
    int i = 0;
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        {
            printf("export: `%s=%s': not a valid identifier\n",str, str1);
            return ;
        }
        addback(&env, key_value(str, str1));
        i++;
    }
}
void add_expo(char **str, ev_list *env)
{
    int i;
    char **tmp;

    i = 1;
    tmp = NULL;
    while (str[i])
    {
        tmp = ft_split(str[i], '=');
        if (check_double(env, tmp[0], tmp[1]))
            expo_pars(tmp[0], tmp[1],env);

        i++;
    }
    free(tmp);
}
void ft_env(ev_list *env, t_exec *cmd)
{
    int flag;

    flag = -1;

    if (ft_strcmp(cmd->args[0], "export") == 0)
        flag = 1;
    if (ft_strcmp(cmd->args[0], "env") == 0)
        flag = 0;
    if ((ft_strcmp(cmd->args[0], "export") == 0 && str_chr(cmd->args)) || (ft_strcmp(cmd->args[0], "export") == 0 && is_alpha(cmd->args)))
        flag = -1;
    if (flag == -1)
        add_expo(cmd->args, env);
    if (flag == 0 || flag == 1)
        print_env(env, flag);
}

void        delet_unset(ev_list **env,char *key)
{
    ev_list *tmp = NULL;
    ev_list *perv;
    // ev_list *earea;


    perv = NULL;
    tmp = (*env);
    if ((*env) != NULL)
    {
        if (ft_strcmp(tmp->key, key) != 0)
        {
            printf("---------\n");
            while (tmp->next)
            {
                if (ft_strcmp(tmp->next->key, key) == 0)
                {
                    perv = tmp->next;
                    free(tmp->next->key);
                    free(tmp->next->value);
                    tmp->next = tmp->next->next;
                    free(perv);
                    return ;
                }
                tmp = tmp->next;
            }
        }
        else
            tmp = (*env);
            (*env) = (*env)->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);

    }
}
void    ft_unset(ev_list **env, t_exec *cmd)
{
    (void)env;
    (void)cmd;
    ev_list *tmp;
    tmp = *env;
    int i = 1;
    while (tmp)
    {
        while (cmd->args[i])
        {
        // printf("----------%s\n",tmp->key);
            if (ft_strcmp(cmd->args[i], tmp->key) == 0)
            {
                delet_unset(&tmp,tmp->key);
                // printf("----%s----\n",tmp->next->value);
                return ;
            }
            else
                break;
            i++;
        }
        tmp = tmp->next;
    }
}
void check_builting(t_exec *cmd, ev_list *env)
{
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("env", cmd->args[i]) == 0)
            ft_env(env, cmd);
        if (ft_strcmp("export", cmd->args[i]) == 0)
            ft_env(env, cmd);
        if (ft_strcmp("unset", cmd->args[i]) == 0)
            ft_unset(&env, cmd);
        if (ft_strcmp("echo", cmd->args[i]) == 0)
            ft_echo(cmd,env);
        i++;
    }
}

void ft_exec(t_exec *exec_cmd, ev_list *env)
{
    check_builting(exec_cmd, env);
}