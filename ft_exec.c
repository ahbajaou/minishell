/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:46:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/09 20:46:55 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
         if (str[i] && str[i] == '-' && str[i + 1] == 'n')
         {
            flag  = 1;
            break ;
         }
        i++;
    }
    if (flag == 1)
        return (0);
    return (1);
}
void    echo_handler(char **args)
{
    int i;

    int flag;

    i = 1;
    flag = 0;
     while (args[i])
     {
            if (ft_strcmp(args[i], "-n") != 0 && handel_q(args[i]) == 1)
            {
                while (args[i])
                {
                    printf("%s",args[i]); 
                    if (args[i + 1] == NULL)
                        break ;
                    printf(" ");
                    i++;
                }
                return ;
            }
        i++;
     }   
}
void    echo_print(char **str)
{
    int i;

    i = 1;
    while (str[i])
    {
        printf("%s",str[i]);
        if (str[i + 1] == NULL)
            break ;
        printf(" ");
        i++;
    }
    printf("\n");
}
void ft_echo(t_exec *cmd, ev_list *env)
{
    int i;

    int flag;

    i = 0;
    flag = 0;
     (void)env;
     while (cmd->args[i])
     {
        if (ft_strcmp(cmd->args[i], "echo") == 0 && ft_strcmp(cmd->args[i + 1], "-n") == 0)
        {
            echo_handler(cmd->args);
            return ;
        }
        if (ft_strcmp(cmd->args[i], "echo") == 0 && ft_strcmp(cmd->args[i + 1], "-n") != 0)
        {
            echo_print(cmd->args);
            return ;
        }
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

    perv = NULL;
    tmp = (*env);
    if ((*env) != NULL)
    {
        if (ft_strcmp(tmp->key, key) != 0)
        {
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
            if (ft_strcmp(cmd->args[i], tmp->key) == 0)
            {
                delet_unset(&tmp,tmp->key);
                return ;
            }
            else
                break;
            i++;
        }
        tmp = tmp->next;
    }
}
void    ft_pwd(t_exec *cmd)
{
    char cwd[256];
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], "pwd") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n",cwd);
            return ;
        }
        i++;
    }
}
void    update_path(ev_list *env, char *old,char *path,char *new)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(old, tmp->key) == 0)
            tmp->value = ft_strdup(new);
        if (ft_strcmp(path, tmp->key) == 0)
            tmp->value = ft_strdup(new);
        tmp = tmp->next;
    }
    free(tmp);
}
void    ft_cd(t_exec *cmd, ev_list *env)
{
    int i;

    i = 0;
    char cwd[256];
    while (cmd->args[i])
    {
        if (ft_strcmp("cd", cmd->args[i]) == 0 && cmd->args[i + 1] == NULL)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
            chdir("..");
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
        else if (ft_strcmp("cd", cmd->args[i]) != 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
                chdir(cmd->args[i]);
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
        i++;
    }
}
void    ft_exit(t_exec *cmd)
{
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], "exit") == 0)
            exit(0);
        i++;
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
        if (ft_strcmp("pwd", cmd->args[i]) == 0)
            ft_pwd(cmd);
        if (ft_strcmp("cd", cmd->args[i]) == 0)
            ft_cd(cmd,env);
        if (ft_strcmp("exit", cmd->args[i]) == 0)
            ft_exit(cmd);
        i++;
    }
}

void ft_exec(t_exec *exec_cmd, ev_list *env)
{
    check_builting(exec_cmd, env);
}