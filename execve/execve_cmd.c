
#include "../minishell.h"


int	ft_slen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_join2(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(ft_slen(s1) + ft_slen(s2) + 1);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		free((char *)s1);
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int    execve_cmd(t_exec *cmd, ev_list **env)
{
    (void)cmd;
    (void)env;

    ev_list *tmp;

    tmp = (*env);
    char *path;
    char **spl;
    spl = NULL;
    while (tmp)
    {
        if (strcmp(tmp->key, "PATH") == 0)
                path = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    spl = ft_split(path, ':');
    int i = 0;
    int j = 0;
    char *current;
    int pid;

    i = 0;
    j = 0;
    char *p;
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        while (cmd->args[i])
        {
            j = 0;
            while (spl[j])
            {
                current = ft_join2(spl[j],"/");
                p = ft_join2(current,cmd->args[i]);
                if (!access(p,F_OK))
                {
                    if (!execve(p,cmd->args,NULL))
                        return (1);
                }

                j++;
            }

            i++;
        }
    }
    return (1);
}
