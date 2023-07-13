#include "minishell.h"

ev_list	*_env(char **envp)
{
    ev_list *env = NULL;

    char **tmp = NULL;

    int i = 0;
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        addback(&env,key_value(tmp[0], tmp[1]));
        i++;
    }
    free(tmp);
    return(env);
}

int main(int argc, char **argv, char **envp)
{
    (void)envp;
    ev_list *env = _env(envp);
;
    (void)argc,(void)argv;
    t_exec *exec_command = NULL;
    t_pipe *pipe_command = NULL;
    t_redir *redirection_command = NULL;

    while(1)
    {
        char *str = readline("minishell: ");
        if (!str)
            return (0);
        add_history(str);
            
        int end = strlen(str);
            t_type *cmd = pipe_commands(&str , str + end, NULL);
            if (cmd == NULL)
                exit(1);
            while(cmd)
            {
                if(cmd->type == 1)
                {
                    exec_command = (t_exec *)cmd;
                    char *expandedValue = func_expand(str);
                    if (expandedValue != NULL)
                        printf("Valeur étendue: %s\n", expandedValue);

                    printf("type de la commande execution : %d\n",exec_command->type);
                    cmd = exec_command->cmd;
                    printf("%s\n",exec_command->args[0]);
                }
                else if(cmd->type == 2)
                {
                    pipe_command = (t_pipe*)cmd;
                    printf("type de la commande pipe : %d\n",pipe_command->type);
                    cmd = pipe_command->rightcmd;
                    // cmd = pipe_command->leftcmd;

                    // cmd = pipe_command->rightcmd;
                }
                else if(cmd->type == 3)
                {
                    redirection_command = (t_redir *)cmd;
                    printf("type de la commande redirection : %d\n",redirection_command->type);
                    printf("%s\n",redirection_command->filename);
                    cmd = redirection_command->cmd;
                }
                else
                    break;
            }
            ft_exec(exec_command,&env,pipe_command);
        }
    return(0);
}
