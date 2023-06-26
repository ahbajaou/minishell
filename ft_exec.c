/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:17:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/26 23:20:28 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

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
char	*ft__strdup(char *str)
{
	int		i;
	char	*dup;

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

void	addback(ev_list **list, ev_list *new)
{
	ev_list	*tmp;

	tmp = *list;
	if (!(*list))
	{
		*list = new;
        return ;
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
                if ((str[i][j] >= 'a' && str[i][j] <= 'z')
                || (str[i][j] >= 'A' && str[i][j] <= 'Z'))
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
void    print_env(ev_list *env,int flag)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (flag == 1 && tmp->key != NULL && tmp->value == NULL)
            printf("declare -x %s\n",tmp->key);
        if (flag == 0 && tmp->key != NULL && tmp->value != NULL)
             printf("%s=%s\n",tmp->key,tmp->value);
        if (flag == 1 && tmp->key != NULL && tmp->value != NULL)
            printf("declare -x %s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    free(tmp);
}

int    check_double(ev_list *env ,char *key, char *value)
{
    (void)env;
    (void)value;

    ev_list *tmp;
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value))
        {
            printf("-------------\n");

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
void    add_expo(char **str, ev_list *env)
{
    int i;
    char **tmp;

    i = 1;
    tmp = NULL;
    while (str[i])
    {
        tmp = ft_split(str[i], '=');
        if (check_double(env,tmp[0],tmp[1]))
                addback(&env, key_value(tmp[0], tmp[1]));

        i++;
    }
    free(tmp);
}
void    ft_env(ev_list *env, t_exec *cmd)
{
    int flag;

    flag  = -1;

    if (ft_strcmp(cmd->args[0], "export") == 0)
        flag  = 1;
      if (ft_strcmp(cmd->args[0], "env") == 0)
        flag  = 0;
     if ((ft_strcmp(cmd->args[0], "export") == 0 && str_chr(cmd->args))
     || (ft_strcmp(cmd->args[0], "export") == 0 && is_alpha(cmd->args)))
        flag  = -1;
    if (flag == -1)
        add_expo(cmd->args, env);
    if (flag == 0 || flag == 1)
        print_env(env,flag);
}

void    check_builting(t_exec *cmd, ev_list *env)
{
    int i;

    i = 0;
    while (cmd->args[i])
    {
        if (ft_strcmp("echo", cmd->args[i]) == 0)
            ft_echo(cmd);
        if (ft_strcmp("env", cmd->args[i]) == 0)
            ft_env(env, cmd);
        if (ft_strcmp("export", cmd->args[i]) == 0)
            ft_env(env, cmd);
        i++;
    }
}

void    ft_exec(t_exec *exec_cmd, ev_list *env)
{
    check_builting(exec_cmd, env);
}