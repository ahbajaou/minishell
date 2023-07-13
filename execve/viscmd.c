


#include "../minishell.h"


void ft_pipe(t_exec *exec_cmd, ev_list **env,t_pipe *pipe_command)
{
    (void)pipe_command;
    (void)env;
    (void)exec_cmd;
    t_pipe *cmd;
    cmd = (t_pipe*)pipe_command;
    // viscmd(exec_cmd, env,(t_pipe *)cmd->rightcmd);
    viscmd(exec_cmd, env,(t_pipe *)cmd->leftcmd);


}
void viscmd(t_exec *exec_cmd, ev_list **env,t_pipe *pipe_command)
{
    (void)pipe_command;
    (void)env;
    (void)exec_cmd;

    // t_exec *bcmd;

        // pipe_command = malloc(sizeof(pipe_command));
        // printf("--%s--\n",exec_cmd->args[0]);
    // if (pipe_command->type)
    // {
    //         printf("--here--\n");
    //     pipe_command->type = EXEC;
    // }
    printf("---recur--\n");
    if (pipe_command->type == PIPE)
    {
        printf("--%d--\n",pipe_command->type);
        printf("start pipe\n");
        ft_pipe(exec_cmd,env,pipe_command);
        
    }
    if (pipe_command->type == EXEC)
    {
        // bcmd = (t_exec *)exec_cmd;
        printf("%s--%s\n",exec_cmd->args[0],exec_cmd->args[1]);
        if (check_builting(exec_cmd, env) == 1)
        {
            if (execve_cmd(exec_cmd, env))
                return ;
            printf("--EXEC--\n");
            // viscmd(exec_cmd,env,(t_pipe *)exec_cmd->cmd);
            // return ;
        }
            
    }
}