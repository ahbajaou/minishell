#ifndef MINISHELL_H
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

typedef struct s_cmd
{
    int type;
}      t_cmd;

typedef struct v_exec
{
    int type;
    char *args[1024];
    int argc;
    t_cmd *cmd;;
}           t_exec;

typedef struct v_pipe
{
    int type;
    struct  s_cmd *right;
    struct  s_cmd *left;
}       t_pipe;
typedef struct v_redir
{
    int type;
    char *file;
    t_cmd  *cmd;
    int open_file;
    int fd;
    int flags;
}       t_redir;

typedef struct v_list
{
    char *content;
    struct v_list *next;
}   t_list;

typedef struct e_list
{
    char *key;
    char *value;
    struct e_list *next;
}   ev_list;



int			get_token(char **str, char *end_str, char **previous, char **ep);
int			check_append(char **ptr);
int			check_herdoc(char **ptr);
int			token(char **ptr, char *end, int tok);

char		*ret_str(char *str, char *end);

void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
// 
t_cmd *create_exec_command(void);
t_cmd *create_pipe_command(t_cmd *right, t_cmd *left);
t_redir *create_redir_command(char *file,int fd, int flags, t_list* env_l);
//
void    skip_quotes(char **ptr, char *end);
int     check_symbol(char *str, char *end, char *symbols);
int     check_for_symbol(char *str, char *end, char *symbols);
char    *handle_quotes_and_dollar(char *str, t_list *envList);
char    *validat_String(char *str, t_list *env_list);
char    find_sym(char *str,char *end);
char    *substr_ing(char **str, char sym);
char    *extractSubstring(char **str, char symbol, t_list *env_list);
char    *str_quotes(char **str, char symbol, t_list *env_list);
char    *process_Dollar(char **str, t_list *env_list);
void	concatenate_Remaining_Strings(char *str, char *stre, char **new, char *join);
//
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin5(char *s1, char *s2);
char	*ft_strdup(const char *s1);
void	check_free(char *str);

int	is_symbol(char *str, char *stre, char *symbol);

t_cmd	*parse_pipe(char **str, char *stre, t_list *env_l);
t_cmd	*parse_exec(char **str, char *stre, t_list *env_l);
t_cmd	*parse_redirs(t_cmd *cmd, char **str, char *stre, t_list *env_l);
t_cmd	*pipe_data(t_cmd *right, t_cmd *left);
t_cmd	*get_cmd(void);
void	set_args(char *str, char **args, int *argc);

ev_list	*_env(char **envp);
void    ft_exec(t_exec *exec_cmd, ev_list *env);
char	**ft_split( char *s, char c);
void	addback(ev_list **list, ev_list *new);
ev_list *key_value(char *key, char *value);
void    execver_cmd(t_exec *cmd, ev_list *env);
int ft_strcmp(char *s1, char *s2);

#endif