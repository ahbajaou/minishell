/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:17:17 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/06/20 00:44:06 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void    ft_exec(t_exec *exec_cmd, char **env)
{
    int i = 0;
    char **getenv;
    while (exec_cmd->args[i])
    {
        i++;
    }
    getenv = ft_split(*env, '=');
    while (i)
    {
        printf("--%s\n",getenv[i]);
        i++;
    }
}