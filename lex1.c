#include "minishell.h"

int	token(char **ptr, char *str_end, int tok)
{
	if (strchr("|<>", tok))
	{
		if (tok == '>')
			tok = check_append(ptr);
		else if (tok == '<')
			tok = check_herdoc(ptr);
		else if (tok == '|')
			(*ptr)++;
	}
	else
	{
		while (*ptr < str_end && !strchr("\t\v\r\n\f ", **ptr)
			&& !strchr("|<>", **ptr))
		{
			if (strchr("'\"", **ptr))
				skip_character(ptr, str_end,**ptr);
			else
				(*ptr)++;
		}
	}
	return (tok);
}

int	get_token(char **str, char *str_end, char **previous, char **ep)
{
	int		tok;
	char	*ptr;

	ptr = *str;
	while (ptr < str_end && strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	if (previous)
		*previous = ptr;
	// printf ("befoere TOK is : %d\n", tok);
 	tok = *ptr;
	if (!tok)
		return (0);
	tok = token(&ptr, str_end, tok);
	if (ep)
		*ep = ptr;
	while (ptr < str_end && strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	*str = ptr;
	return (tok);
}


