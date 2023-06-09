#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include "minishell.h"

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


int main()
{
    char *input;
    while (1)
    {
        char *input = readline("minishell $: ");
        if (!input)
            exit(1);
    }
    printf("--%s\n",input);
    char *end = input + strlen(input);

    t_exec *exec_cmd ;
    t_pipe *pipe_cmd ;
    t_redir *redir_cmd ;
    t_cmd *cmd = parse_pipe(&input,end,NULL);
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
            cmd = pipe_cmd->right;
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
    ft_exec(exec_cmd);
}
