#include "minishell.h"



// t_list	*env(t_list *list, char **envt)
// {
// 	t_list *head = NULL;
// 	t_list *current = NULL;
// 	int i = 0;

// 	while (envt[i] != NULL)
// 	{
// 		t_list *node = (t_list *)malloc(sizeof(t_list));
// 		node->content = strdup(envt[i]);
// 		node->next = NULL;
// 		if (head == NULL)
// 		{
// 			head = node;
// 			current = node;
// 		}
// 		else
// 		{
// 			current->next = node;
// 			current = current->next;
// 		}
// 		i++;
// 	}
// 	return head;
// }


