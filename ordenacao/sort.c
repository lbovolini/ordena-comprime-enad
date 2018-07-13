#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "string_aux.h"


void insertionsort (char **arquivo_memoria, int *indice_linhas, 
    int **indice_separadores, int coluna1, int num_linhas)
{
    if (!arquivo_memoria) {
        printf ("Erro insertion_sort_2()\n");
        exit (EXIT_FAILURE);
    }

    for (int i = 1; i < num_linhas; i++) 
    {
        int atual = indice_linhas[i];
        int *atual_separador = indice_separadores[indice_linhas[i]];
        int j = i - 1;

        char *str1 = NULL, 
             *str2 = NULL;

        free(str1);
        free(str2);
        str1 = get_substring (*(arquivo_memoria + indice_linhas[i]), 
             indice_separadores[indice_linhas[i]][coluna1 - 1], 
             indice_separadores[indice_linhas[i]][coluna1]);

        str2 = get_substring (*(arquivo_memoria + indice_linhas[j]), 
             indice_separadores[indice_linhas[j]][coluna1 - 1], 
             indice_separadores[indice_linhas[j]][coluna1]);


        while ((j >= 0) && (strcasecmp (str1, str2) > 0)) 
        {
            indice_linhas[j + 1] = indice_linhas[j];
            indice_separadores[indice_linhas[j + 1]] = indice_separadores[indice_linhas[j]];

            free(str2);
            j = j - 1;
            str2 = get_substring (*(arquivo_memoria + indice_linhas[j]), 
                 indice_separadores[indice_linhas[j]][coluna1 - 1], 
                 indice_separadores[indice_linhas[j]][coluna1]);

        }
        indice_linhas[j + 1] = atual;
        indice_separadores[indice_linhas[j + 1]] = atual_separador;
    }
}


void quicksort_string (char **arquivo_memoria, int *indice_linhas, 
    int **indice_separadores, int coluna1, int num_linhas, int esquerda, int direita)
{
    int i, 
        j;

    char *pivo, 
         *p1, 
         *p2;

    i = esquerda;
    j = direita;
    pivo = get_substring (*(arquivo_memoria + indice_linhas[(esquerda + direita) / 2]), 
        indice_separadores[indice_linhas[(esquerda + direita) / 2]][coluna1 - 1], 
        indice_separadores[indice_linhas[(esquerda + direita) / 2]][coluna1]);


    do {
        p1 = get_substring (*(arquivo_memoria + indice_linhas[i]), 
            indice_separadores[indice_linhas[i]][coluna1 - 1], 
            indice_separadores[indice_linhas[i]][coluna1]);

        while ((strcasecmp (p1, pivo) < 0) && (i < direita)) 
        {
            i++;
            p1 = get_substring (*(arquivo_memoria + indice_linhas[i]), 
                indice_separadores[indice_linhas[i]][coluna1 - 1], 
                indice_separadores[indice_linhas[i]][coluna1]);

        }
        p2 = get_substring (*(arquivo_memoria + indice_linhas[j]), 
            indice_separadores[indice_linhas[j]][coluna1 - 1], 
            indice_separadores[indice_linhas[j]][coluna1]);

        while ((strcasecmp (p2, pivo) > 0) && (j > esquerda)) 
        {
            j--;
            p2 = get_substring (*(arquivo_memoria + indice_linhas[j]), 
            indice_separadores[indice_linhas[j]][coluna1 - 1], 
            indice_separadores[indice_linhas[j]][coluna1]);

        }
        if (i <= j) 
        {            
            int temp;
            int *p;

            temp = indice_linhas[i];
            p = indice_separadores[indice_linhas[i]];
            indice_linhas[i] = indice_linhas[j];
            indice_separadores[indice_linhas[i]] = indice_separadores[indice_linhas[j]]; 
            indice_linhas[j] = temp;
            indice_separadores[indice_linhas[j]] = p;
            i++;
            j--;
        }
    } while (i <= j);

    if (esquerda < j) {
        quicksort_string (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, esquerda, j);
    }
    if (i < direita) {
        quicksort_string (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, i, direita);
    }
}


void quicksort_number (char **arquivo_memoria, int *indice_linhas, 
    int **indice_separadores, int coluna1, int num_linhas, int esquerda, int direita)
{
    int i, j;
    float pivo, p1, p2;

    i = esquerda;
    j = direita;
    pivo = get_number (*(arquivo_memoria + indice_linhas[(esquerda + direita) / 2]), 
        indice_separadores[indice_linhas[(esquerda + direita) / 2]][coluna1 - 1], 
        indice_separadores[indice_linhas[(esquerda + direita) / 2]][coluna1]);

    do {
        p1 = get_number (*(arquivo_memoria + indice_linhas[i]), 
            indice_separadores[indice_linhas[i]][coluna1 - 1], 
            indice_separadores[indice_linhas[i]][coluna1]);

        while ((p1 < pivo) && (i < direita)) 
        {
            i++;
            p1 = get_number (*(arquivo_memoria + indice_linhas[i]), 
                indice_separadores[indice_linhas[i]][coluna1 - 1], 
                indice_separadores[indice_linhas[i]][coluna1]);

        }
        p2 = get_number (*(arquivo_memoria + indice_linhas[j]), 
            indice_separadores[indice_linhas[j]][coluna1 - 1], 
            indice_separadores[indice_linhas[j]][coluna1]);

        while ((p2 > pivo) && (j > esquerda)) 
        {
            j--;
            p2 = get_number (*(arquivo_memoria + indice_linhas[j]), 
            indice_separadores[indice_linhas[j]][coluna1 - 1], 
            indice_separadores[indice_linhas[j]][coluna1]);

        }
        if (i <= j) 
        {            
            int temp;
            int *p;

            temp = indice_linhas[i];
            p = indice_separadores[indice_linhas[i]];
            indice_linhas[i] = indice_linhas[j];
            indice_separadores[indice_linhas[i]] = indice_separadores[indice_linhas[j]]; 
            indice_linhas[j] = temp;
            indice_separadores[indice_linhas[j]] = p;
            i++;
            j--;
        }
    } while (i <= j);

    if (esquerda < j) {
        quicksort_number (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, esquerda, j);
    }
    if (i < direita) {
        quicksort_number (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, i, direita);
    }
}


/*
void *bubblesort (char **arquivo_memoria, int *indice_linhas, 
    int **indice_separadores, int coluna1, int num_linhas)
{
    if (!arquivo_memoria) {
        printf ("Erro insertion_sort()\n");
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < num_linhas; i++) 
    {
        for (int j = i; j < num_linhas; j++) 
        {
            char *str1 = NULL, 
                 *str2 = NULL;
 
            str1 = get_substring (*(arquivo_memoria + indice_linhas[i]), 
                         indice_separadores[indice_linhas[i]][coluna1 - 1], 
                         indice_separadores[indice_linhas[i]][coluna1]);

            str2 = get_substring (*(arquivo_memoria + indice_linhas[j]), 
                         indice_separadores[indice_linhas[j]][coluna1 - 1], 
                         indice_separadores[indice_linhas[j]][coluna1]);

            if (strcasecmp (str1, str2) > 0) {
                // Troca
                int temp;
                int *p;
                temp = indice_linhas[i];
                p = indice_separadores[indice_linhas[i]];
                indice_linhas[i] = indice_linhas[j];
                indice_separadores[indice_linhas[i]] = indice_separadores[indice_linhas[j]]; 
                indice_linhas[j] = temp;
                indice_separadores[indice_linhas[j]] = p;
            }
            free(str1);
            free(str2);
        }
    }
}*/
