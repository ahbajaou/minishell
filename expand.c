#include "minishell.h"

char* func_expand(char *str)
{
    char *key = strchr(str, '$');
    if (key != NULL)
    {
        key++;
        char *end = strchr(key, ' ');
        if (end != NULL)
            *end = '\0';
        char *value = getenv(key);
        if (value != NULL)
            return value;
    }
    return NULL;
}

