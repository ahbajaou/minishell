#include "minishell.h"

char	find_sym(char *str, char *stre)
{
	while (str < stre)
	{
		if (strchr("\"'$", *str))
			return (*strchr("\"'$", *str));
		str++;
	}
	return (0);
}


char    *substr_ing(char **str, char sym)
{
   char *stop_pos = strchr(*str, sym);
    if (*str < stop_pos)
    {
        char *extracted = ret_str(*str, stop_pos);
        *str = stop_pos;
        return extracted;
    }
    return NULL;
}

char *extractSubstring(char **str, char symbol, t_list *env_list)
{
    if (symbol == '"' || symbol == '\'')
        return str_quotes(str, symbol, env_list);

    if (symbol == '$')
        return process_Dollar(str, env_list);

    return NULL;
}

char *str_quotes(char **str, char symbol, t_list *env_list)
{
    (void)env_list;
    char *start = *str + 1; // Ignorer le symbole de début (guillemet ou apostrophe)
    char *end = strchr(start, symbol); // Trouver la position du symbole de fin

    if (end != NULL)
    {
        size_t length = end - start; // Calculer la longueur de la sous-chaîne
        char *extracted = malloc((length + 1) * sizeof(char)); // Allouer de la mémoire pour la sous-chaîne extraite
        strncpy(extracted, start, length); // Copier la sous-chaîne dans extracted
        extracted[length] = '\0'; // Ajouter le caractère de fin de chaîne

        *str = end + 1; // Mettre à jour le pointeur *str pour pointer après le symbole de fin
        return extracted;
    }

    return NULL;
}

char *process_Dollar(char **str, t_list *env_list)
{
    (void)env_list;
    char *start = *str + 1; // Ignorer le symbole de début ('$')
    char *end = strchr(start, ' '); // Trouver la position de l'espace ou du prochain séparateur

    if (end != NULL)
    {
        size_t length = end - start; // Calculer la longueur du nom de variable
        char *var_name = malloc((length + 1) * sizeof(char)); // Allouer de la mémoire pour le nom de variable
        strncpy(var_name, start, length); // Copier le nom de variable dans var_name
        var_name[length] = '\0'; // Ajouter le caractère de fin de chaîne

        *str = end; // Mettre à jour le pointeur *str pour pointer sur l'espace ou le séparateur

        // Effectuer le traitement approprié sur var_name (par exemple, récupérer sa valeur à partir de env_l)
        return var_name;
    }
    return NULL;
}

