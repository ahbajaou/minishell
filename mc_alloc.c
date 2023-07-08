#include "minishell.h"

t_type *create_data_exec(void)
{
    t_exec  *cmd;
    cmd = (t_exec*)calloc(1,sizeof(t_exec));
    cmd->type = EXEC;
    return ((t_type*)cmd);
}

t_type *create_data_pipe(t_type *right_cmd,t_type *left_cmd)
{
    t_pipe  *pipe;

    pipe = (t_pipe*)calloc(1,sizeof(t_pipe));
    pipe->type = PIPE ;
    pipe->rightcmd = right_cmd;
    pipe->leftcmd = left_cmd;
    return ((t_type*)pipe);
}

t_redir *create_data_redir(char *filename,int fd,int flags,t_copy *env)
{
    t_redir *redir;

    redir = (t_redir*)calloc(1,sizeof(t_redir));
    redir->type = REDIR;
    redir->flags = flags;
    redir->filename = check_special(filename,env);
    redir->fd = fd;
    return(redir);
}

void    add_arg_to_list(char *str,char **args,int *argc)
// La fonction add_arg_to_list semble être utilisée pour traiter une chaîne de caractères
// str et décider si elle doit être enregistrée comme une commande dans args 
// ou si la mémoire doit être libérée si str est une chaîne vide.
{
    if(*str)
    {
        if(*str)
        {
            *args = str;
            *argc = *argc +1;
        }
        else
            free(str);
    }
}

