#include "minishell.h"

int	check_append(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '>';
	if (**ptr == '>')
	{
		(*ptr)++;
		tok = '+';
	}
	return (tok);
}

int	check_herdoc(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '<';
	if (**ptr == '<')
	{
		(*ptr)++;
		tok = '*';
	}
	return (tok);
}
void	skip_quotes(char **ptr, char *end)
{
	char	q;
	char	*p;

	q = **ptr;
	p = *ptr;
	p++;
	while (p < end && *p != q)
		p++;
	if (p < end && *p == q)
		p++;
	*ptr = p;
}

int	token(char **ptr, char *end, int tok)
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
		while (*ptr < end && !strchr("\t\v\r\n\f ", **ptr)
			&& !strchr("|<>", **ptr))
		{
			if (strchr("'\"", **ptr))
				skip_quotes(ptr, end);
			else
				(*ptr)++;
		}
	}
	return (tok);
}

int	get_token(char **str, char *end, char **previous, char **ep)
{
	int		tok;
	char	*ptr;

	ptr = *str;
	while (ptr < end && strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	if (previous)
		*previous = ptr;
 	tok = *ptr;
	if (!tok)
		return (0);
	tok = token(&ptr, end, tok);
	if (ep)
		*ep = ptr;
	while (ptr < end && strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	*str = ptr;
	return (tok);
}


