/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:54:35 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/11 23:58:49 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_pipe(t_exec *cmd,t_pipe *pipe)
{
    (void)cmd;
    (void)pipe;
    if (pipe->leftcmd->type == 1)
        printf("--start--\n");
    printf("--%d--\n",pipe->leftcmd->type);
    printf("--%d--\n",pipe->rightcmd->type);
    printf("==%s==\n",cmd->args[0]);
    printf("--here--\n");
}