# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXEC 1
# define PIPE 2
# define REDIR 3
# define HERDOC 4

typedef struct v_type
{
    int type;
}      t_type;

typedef struct v_exec
{
    int type;
    char *args[1024];
    int argc;
    t_type *cmd;
}           t_exec;

typedef struct v_pipe
{
    int type;
    struct  v_type *rightcmd;
    struct  v_type *leftcmd;
}       t_pipe;

typedef struct v_redir
{
    int type;
    char *filename;
    t_type  *cmd;
    int open_file;
    int fd;
    int flags;
}       t_redir;

typedef struct v_copy
{
    char *content;
    struct v_copy *next;
}   t_copy;

typedef struct e_list
{
    char *key;
    char *value;
    struct e_list *next;
}   ev_list;

/*lexer*/
int	get_token(char **str, char *str_end, char **previous, char **ep);
int	token(char **ptr, char *str_end, int tok);
/*lexer_func*/
char	*substring_copy(char *str, char *after_str);


/* parser_ */
t_type	*pipe_commands(char **str, char *str_end, t_copy *env);
t_type	*single_command(char **str, char *str_end, t_copy *env);
t_type *redirection_commands(t_type *cmd,char **str,char *str_end,t_copy *env);

/*annexe_func_parse*/
void    add_arg_to_list(char *str,char **args,int *argc);

/*allocation*/
t_type *create_data_exec(void);
t_type *create_data_pipe(t_type *right_cmd,t_type *left_cmd);
t_redir *create_data_redir(char *filename,int flags,int fd,t_copy *env);

/*cheaker*/
int ft_check_chock(char *str,char *str_end,char *symbol);
int ft_spaces(char *str,char *str_end,char *symbol);
int check_for_symbol(char *str, char *end, char *symbols);
int	check_append(char **ptr);
int	check_herdoc(char **ptr);


/*handle $ "" */
char    *check_special(char *str,t_copy *env);
char    *handle_quotes_and_dollar(char *str,t_copy *env);
char    find_sym(char *str,char *stre);
char    *substr_ing(char **str, char sym);
char *extract_substring(char **str,char symbol,t_copy *env);
char	*ft_strjoin_allfree(char *s1, char *s2);
char	*ft_strjoin__just1_free(char *s1, char *s2);
void	free_s1_s2(char *str);
char	*ft_strdup(const char *s1);
void	concatenate_remaining_strings(char *str, char *stre, char **new, char *join);
void    skip_character(char **ptr,char *end,char targer);
char *h_quotes(char **str,char symbol,t_copy *env);
char *h_dollar(char **str, t_copy *env);
 

/*env*/



/*expand*/
char* func_expand(char *str);

/*exec*/
ev_list	*_env(char **envp);
void ft_exec(t_exec *exec_cmd, ev_list **env,t_pipe *pipe_command);
void    ft_pipe(t_exec *cmd,t_pipe *pipe);
char	**ft_split( char *s, char c);
void	addback(ev_list **list, ev_list *new);
int    execve_cmd(t_exec *exec_cmd, ev_list **env);
ev_list *key_value(char *key, char *value);

#endif