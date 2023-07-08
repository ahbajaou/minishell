#include "minishell.h"

void print_env(t_copy *env)
{
    t_copy *current = env;

    while (current != NULL)
    {
        printf("%s\n", current->content);
        current = current->next;
    }
}

t_copy	*env(t_copy *list, char **env)
{
	(void)list;
	t_copy *head = NULL;
	t_copy *current = NULL;
	int i = 0;

	while (env[i] != NULL)
	{
		t_copy *node = (t_copy *)malloc(sizeof(t_copy));
		node->content = strdup(env[i]);
		node->next = NULL;
		if (head == NULL)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = current->next;
		}
		i++;
	}
	return head;
}