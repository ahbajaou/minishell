#include "minishell.h"

t_type	*pipe_commands(char **str, char *str_end, t_copy *env)
{
   t_type *cmd;

   cmd = single_command(str,str_end,env);
   if(ft_check_chock(*str,str_end,"|"))
   {
        if (!*((t_exec *)cmd)->args && !((t_exec *)cmd)->cmd)
			return (NULL);// si la commande est vide apres le pipe
        get_token(str,str_end,0,0);
        cmd = create_data_pipe(cmd,pipe_commands(str,str_end,env));
   }
    return (cmd);
}

t_type	*single_command(char **str, char *str_end, t_copy *env)
{
    t_exec *exec_cmd;
    t_type *cmd;
    char *ptr;
    char *ptr_end;

    exec_cmd = (t_exec*)create_data_exec();
    exec_cmd->argc = 0;
    cmd = (t_type*)exec_cmd; //polymorphisme
    cmd = redirection_commands(cmd,str,str_end,env);
    while (!ft_check_chock(*str,str_end,"|"))
    {
        if(get_token(str,str_end,&ptr,&ptr_end) == 0)
            break;
        else
            add_arg_to_list(substring_copy(ptr,ptr_end), &exec_cmd->args[exec_cmd->argc],&exec_cmd->argc);
        cmd = redirection_commands(cmd,str,str_end,env);
    }
    exec_cmd->args[exec_cmd->argc] = 0; // P,NULL
    return((t_type*)cmd);
}

int	redir_error(int tok)
{

	if (!tok)
		return (1);
	return (0);
}

t_type  *reverse_command(t_type *cmd1, t_type *cmd2)
{
    if (cmd1->type == REDIR)
        return(((t_redir*)cmd1)->cmd = cmd2);
    if (cmd1->type == EXEC)
        return(((t_exec*)cmd1)->cmd = cmd2);
    return(cmd2);
}

t_type *redirection_commands(t_type *cmd,char **str,char *str_end,t_copy *env)
{
    char *ptr;
    char *ptr_end;
    int token;
    t_redir *redir_cmd;

    while (ft_spaces(*str,str_end,"<>+"))
    {
        // token = get_token(str,str_end,&ptr,&ptr_end);
        token = get_token(str,str_end,0,0);
        printf("%s\n", *str);
        if(redir_error(get_token(str,str_end,&ptr,&ptr_end)))
            return(NULL);
        if(token == '>')
            redir_cmd = create_data_redir(substring_copy(ptr,ptr_end),O_WRONLY | O_TRUNC, 1,env);
        else if(token == '<')
            redir_cmd = create_data_redir(substring_copy(ptr,ptr_end), O_RDONLY, 0, env);
        else if(token == '+')
            redir_cmd = create_data_redir(substring_copy(ptr,ptr_end),O_RDWR | O_APPEND, 1, env);
        // else if (tok == '*')
			// hd = create_data_redir(substring_copy(p, pe), O_CREAT | O_RDWR | O_TRUNC, 1);
        if(strchr("<>+",token))
            cmd = reverse_command(cmd,(t_type*)redir_cmd);
        // else if(token == '*')
        //     cmd = reverse_command(cmd, (t_cmd *)hd)
    }
    return(cmd);
}