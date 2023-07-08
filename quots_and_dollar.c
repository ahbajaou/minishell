#include "minishell.h"

char *h_quotes(char **str,char symbol,t_copy *env)
{
    (void)env;
    char *start = *str + 1; // Ignorer le symbole de début (guillemet ou apostrophe)
    char *end = strchr(start,symbol);// Trouver la position du symbole de fin

    if (end != NULL)
    {
        size_t length = end - start; // Calculer la longueur de la sous-chaîne
        char *extracted = malloc(sizeof(char) * (length + 1)); // Allouer de la mémoire pour la sous-chaîne extraite
        strncpy(extracted, start, length); // Copier la sous-chaîne dans extracted
        extracted[length] = '\0'; // Ajouter le caractère de fin de chaîne

        *str = end + 1; // Mettre à jour le pointeur *str pour pointer après le symbole de fin
        return extracted;
    }

    return NULL;
}

char *h_dollar(char **str, t_copy *env)
{
    (void)env;

    char *start = *str + 1;
    char *end = strchr(start,' ');

    if(end != NULL)
    {
        size_t lenght = end - start ;
        char *extracted = malloc(sizeof(char)  * (lenght + 1));
        strncpy(extracted,start,lenght);
        extracted[lenght] = '\0';
        *str = end + 1;
        return extracted ;
    }
    return NULL;
}

void    skip_character(char **ptr,char *end,char target)
{
    char *p;

    p = *ptr;
    p++;

    while(p < end && *p != target)
        p++;
    if(p < end && *p == target)
        p++;
    *ptr = p;
}


