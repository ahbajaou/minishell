#include "minishell.h"

void print_env(t_list *env)
{
    t_list *current = env;

    while (current != NULL)
    {
        printf("%s\n", current->content);
        current = current->next;
    }
}

t_list	*env(t_list *list, char **envt)
{
	(void)list;
	t_list *head = NULL;
	t_list *current = NULL;
	int i = 0;

	while (envt[i] != NULL)
	{
		t_list *node = (t_list *)malloc(sizeof(t_list));
		node->content = strdup(envt[i]);
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