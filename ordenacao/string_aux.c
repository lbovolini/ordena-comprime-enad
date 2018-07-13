#include <stdio.h>
#include <stdlib.h>
#include "string_aux.h"

// Retorna substring
char *get_substring (char *string, int inicio, int fim)
{
    if (inicio == fim) {
        printf ("Erro get_substring() Ini: %d  Fim: %d\n", inicio, fim); 
        exit (EXIT_FAILURE);
    }

    int i = 0;
    char *substring = NULL;
    fim--;

    if (!string) {
        printf ("Erro get_substring()\n");
        exit (EXIT_FAILURE);
    }

    if (!(substring = (char*) malloc ((fim - inicio) * sizeof (char)))) {
        printf ("Erro get_substring()\n");
        exit (EXIT_FAILURE);
    }

    while (i < (fim - inicio)) {
        substring[i] = string[inicio + i];
        i++;
    }
    substring[i] = '\0';

    return substring;
}


// SE COLUNA VAZIA, TIPO?
float get_number (char *string, int inicio, int fim)
{
    float num;
    char *substring = NULL;

    if (!string) {
        printf ("Erro get_num()\n");
        exit (EXIT_FAILURE);
    }
    if (string[inicio] == '"') {
        inicio++;
        fim--;
    }

    substring = get_substring (string, inicio, fim);
    num = atof (substring);

    return num;
}