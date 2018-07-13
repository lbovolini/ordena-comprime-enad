/* !TODO
* - Ordenar por 2 colunas
* - Comentar
*/

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "string_aux.h"
#include "aux.h"

#define NUMBER 0
#define STRING 1
#define N 26162

// get_tipo_coluna();
int const indice_tipo_coluna[156] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


// argc1 => arquivo
// argv2 => coluna1
// argv3 => coluna2
// argv4 => algoritmo

int main (int argc, char **argv) 
{
    FILE *arquivo_entrada = NULL;

    int coluna1 = 0;
    int num_linhas = N;
    int num_separadores = 156;
    int indice_linhas[num_linhas];

    int **indice_separadores;
    char **arquivo_memoria;
    //long start_time, end_time;

    if (argc != 3) {
        printf ("Uso: %s <arquivo> <coluna1>\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    arquivo_entrada = fopen (argv[1], "r");
    if (!arquivo_entrada) {
        printf ("Erro ao abrir o arquivo"); 
        exit (EXIT_FAILURE);
    }


    coluna1 = atoi (argv[2]);
    if ((coluna1 < 1) || (coluna1 > 155)) {
        printf ("Coluna1 invalida\n");
        exit (EXIT_FAILURE);
    }

    inicializa_indice_linhas (indice_linhas, num_linhas);
    indice_separadores = aloca_indice_separadores (num_separadores, num_linhas);
    arquivo_memoria = carrega_arquivo_memoria (arquivo_entrada, num_linhas);
 
    fclose (arquivo_entrada);

    inicializa_indice_separadores (arquivo_memoria, indice_separadores, num_linhas);

    //start_time = wtime();

    if (indice_tipo_coluna[coluna1 - 1] == NUMBER) {
        quicksort_number (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, 1, num_linhas - 1);
    }
    else {
        quicksort_string (arquivo_memoria, indice_linhas, indice_separadores, coluna1, num_linhas, 1, num_linhas - 1);
    }

    //end_time = wtime();
    //printf("Tempo de calculo = %ld us = %ld s\n", (long) (end_time - start_time), ((long) (end_time - start_time)) / 1000000) ;

    imprime_arquivo (arquivo_memoria, indice_linhas, num_linhas);

    return EXIT_SUCCESS;
}