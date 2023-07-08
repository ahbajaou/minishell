# include "minishell.h"

t_cmd *create_exec_command(void)
{
    t_exec *exec;
    exec = (t_exec *)malloc(sizeof(t_exec));
    if (exec == NULL) 
    {
        printf("e");
        return NULL;
    }
    memset(exec, 0, sizeof(t_exec));
    exec->type = EXEC;
    return (t_cmd*)exec;
}

t_cmd *create_pipe_command(t_cmd *right, t_cmd *left)
{
    t_pipe *pipe;
    pipe = (t_pipe*)malloc(sizeof(t_pipe));
    if (pipe == NULL) 
    {
        printf("Erreur d'allocation de mémoire.\n");
        return NULL;
    }
    memset(pipe, 0, sizeof(t_pipe));
    pipe->type = PIPE;
    pipe->right = right;
    pipe->left = left;
    return (t_cmd*)pipe;
}

t_redir *create_redir_command(char *file,int fd, int flags,t_list *env_list)
{
    t_redir *redir;

    redir = (t_redir*)calloc(1,sizeof(t_redir));
    redir->type = REDIR;
    redir->file = validat_String(file,env_list);
    redir->fd = fd;
    redir->flags = flags;
    return(redir);
}

// int main()
// {
//     char *input = strdup("cmd | cat > file");
//     char *end = input + strlen(input);

//     t_exec *exec_cmd ;
//     t_pipe *pipe_cmd ;
//     t_redir *redir_cmd ;
//     t_cmd *cmd = parse_pipe(&input,end,NULL);

//     while(cmd)
//     {
//         // char *str = readline("minishell: ");
//         // if (!str)
//         //     exit(1);
//         if(cmd->type == 3)
//         {
//             redir_cmd = (t_redir *)cmd;
//             printf("Type de la commande redirection : %d\n", redir_cmd->type);
//             printf("%s\n",redir_cmd->file);
//             cmd = redir_cmd->cmd;
//         }
//         else if(cmd->type == 2)
//         {
//             pipe_cmd = (t_pipe*)cmd;
//             printf("Type de la commande pipe : %d\n", pipe_cmd->type);
//             cmd = pipe_cmd->right;
//         }
//         else if (cmd->type == 1)
//         {
            
//             exec_cmd = (t_exec *)cmd;
//             printf("Type de la commande exécution : %d\n", exec_cmd->type);
//             printf("%s\n",exec_cmd->args[0]);
//             cmd = exec_cmd->cmd;
//       }
//       else 
//         break;
//     }
// }

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
    ev_list *env = _env(envp);
    // t_list *envt = env1(NULL, envp);

    // print_env(envt);
	(void)argc, (void)argv;
    t_exec *exec_cmd = NULL;
    t_pipe *pipe_cmd = NULL;
    t_redir *redir_cmd = NULL;
    while(1)
    {
        char *str = readline("minishell: ");
        if (!str)
            exit(1);
        int end = strlen(str);
        t_cmd *cmd = parse_pipe(&str, str + end, NULL);
        if (cmd == NULL) {
            exit(1);
        }
        while(cmd)
        {
            if(cmd->type == 3)
            {
                redir_cmd = (t_redir *)cmd;
                printf("Type de la commande redirection : %d\n", redir_cmd->type);
                printf("%s\n",redir_cmd->file);
                cmd = redir_cmd->cmd;
            }
            else if(cmd->type == 2)
            {
                pipe_cmd = (t_pipe*)cmd;
                printf("Type de la commande pipe : %d\n", pipe_cmd->type);
                cmd = pipe_cmd->left;
            }
            else if (cmd->type == 1)
            {

                exec_cmd = (t_exec *)cmd;
                printf("Type de la commande exécution : %d\n", exec_cmd->type);
                printf("%s\n",exec_cmd->args[0]);
                cmd = exec_cmd->cmd;
            }
            else 
                break;
        }
        // free(str);
        ft_exec(exec_cmd, env);
    }

    return 0;
}