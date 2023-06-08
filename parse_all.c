#include "minishell.h"

t_cmd	*parse_pipe(char **str, char *stre, t_list *env_l)
{
	t_cmd	*cmd;
	
	cmd = parse_exec(str, stre, env_l);
	if (is_symbol(*str, stre, "|"))
	{
		if (!*((t_exec *)cmd)->args && !((t_exec *)cmd)->cmd)
		{
			return (NULL);// si la commande est vide apres le pipe
		}
		get_token(str, stre, 0, 0);
		cmd = pipe_data(cmd, parse_pipe(str, stre, env_l));
	}
	return (cmd);
}

t_cmd	*parse_exec(char **str, char *stre, t_list *env_l)
{
	t_exec	*ecmd;
	t_cmd	*cmd;
	char	*p;
	char	*pe;

	ecmd = (t_exec *)get_cmd();
	ecmd->argc = 0;
	cmd = (t_cmd *)ecmd;
	cmd = parse_redirs(cmd, str, stre, env_l);
	while (!is_symbol(*str, stre, "|"))
	{
		if (get_token(str, stre, &p, &pe) == 0)
			break ;
		else
		{
			set_args(ret_str(p, pe),&ecmd->args[ecmd->argc], &ecmd->argc);
			
		}
			
		cmd = parse_redirs(cmd, str, stre, env_l);
	}
	ecmd->args[ecmd->argc] = 0;
	return ((t_cmd *)ecmd);
}

int	redir_error(int tok)
{

	if (!tok)
	{
	
		return (1);
	}
	return (0);
}

t_cmd	*reverse_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	t_redir		*rcmd;
	t_exec		*ecmd;

	if (cmd1->type == REDIR)
	{
		rcmd = (t_redir *)cmd1;
		rcmd->cmd = cmd2;
		return (rcmd->cmd);
	}
	else if (cmd1->type == EXEC)
	{
		ecmd = (t_exec *)cmd1;
		ecmd->cmd = cmd2;
		return (ecmd->cmd);
	}
	return (cmd2);
}
t_cmd	*parse_redirs(t_cmd *cmd, char **str, char *stre, t_list *env_l)
{
	char		*p  ;
	char		*pe ;
	int			tok;
	t_redir		*rcmd;

	while (is_symbol(*str, stre, "<>+"))
	{
		tok = get_token(str, stre, 0, 0);
		printf("%s\n", *str);
		if (redir_error(get_token(str, stre, &p, &pe)))
			return (NULL);
		if (tok == '>')
			rcmd = create_redir_command(ret_str(p, pe), O_WRONLY | O_TRUNC, 1, env_l);
		else if (tok == '<')
			rcmd = create_redir_command(ret_str(p, pe), O_RDONLY, 0, env_l);
		else if (tok == '+')
			rcmd = create_redir_command(ret_str(p, pe), O_RDWR | O_APPEND, 1, env_l);
		// else if (tok == '*')
		// 	hd = heredoc_data(ret_str(p, pe), O_CREAT | O_RDWR | O_TRUNC, 1);
		if (strchr("<>+", tok))
			cmd = reverse_cmd(cmd, (t_cmd *)rcmd);
		// else if (tok == '*')
		// 	cmd = reverse_cmd(cmd, (t_cmd *)hd);
	}
	return (cmd);
}

t_cmd	*pipe_data(t_cmd *right, t_cmd *left)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)calloc(1, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->right = right;
	pipe->left = left;
	return ((t_cmd *)pipe);
}

t_cmd	*get_cmd(void)
{
	t_exec	*cmd;

	cmd = (t_exec *)calloc(1, sizeof(t_exec));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

void	input_cmd(char **args, int *argc, char *str)
{
	*args = str;
	*argc = *argc + 1;
}

void	set_args(char *str, char **args, int *argc)
{
	if (str)
	{
		if (*str)
			input_cmd(args, argc, str);
		else
			free(str);
	}
}
