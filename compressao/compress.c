/* !TODO
* - Inserir arvore no arquivo comprimido
* - Descomprimir
* - Dividir em arquivos
* - Comentar
*/

#include <stdio.h>
#include <stdlib.h>

#define BIT_MAIS_BAIXO 1

typedef struct code {
	
	int *code;
	char caracter;
	int tam;
} bin_code;

typedef struct lista {

	char caracter;
	int cont;
	struct lista *prox,
				 *esq,
			     *dir;
} st_lista;


typedef struct descritor_lista {

	int n;
	st_lista *prim;
} descritor_lista;


int CODE_MAX_SIZE = 0;
bin_code *codigos_bin;
int codigos_index = 0;


// Cria descritor lista e retorna
descritor_lista *cria_descritor_lista(void)
{
    descritor_lista *descritor = NULL;

    if(!(descritor = (descritor_lista*)malloc(sizeof(descritor_lista))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }

    descritor->n = 0;
    descritor->prim = NULL;

    return descritor;
}


// Cria lista e retorna
st_lista *cria_lista(char caracter)
{
	st_lista *nova = NULL;

	if(!(nova = (st_lista*)malloc(sizeof(st_lista))))
    {
        printf("Falta de memoria!\n");
        exit(EXIT_FAILURE);
    }

    nova->caracter = caracter;
    nova->cont = 1;
    nova->prox = NULL;
	nova->esq = NULL;
	nova->dir = NULL;

    return nova;
}


/* Busca caracter na lista, se encontrado 
retorna sua posicao, se nao retorna NULL */
st_lista *busca_caracter(descritor_lista *descritor, char caracter)
{
	st_lista *percorrer = NULL;

	percorrer = descritor->prim;

	if(!percorrer) return NULL;

	while(percorrer) {
		if(percorrer->caracter == caracter)
			return percorrer;
		percorrer = percorrer->prox;
	}

    // nao encontrado
    return NULL;
}


// Insere na lista
void *insere_lista(descritor_lista *descritor, char caracter)
{
	st_lista *existe = NULL;

	if(!descritor) return NULL;

	// Busca caracter na lista
	existe = busca_caracter(descritor, caracter);

	if(!existe) {
		st_lista *lista = NULL,
				 *percorrer = NULL;

		lista = cria_lista(caracter);

		// Lista vazia
		if(descritor->prim == NULL) {
			descritor->prim = lista;
		}
		else {
			// Insere no fim
			percorrer = descritor->prim;

			while(percorrer->prox)
				percorrer = percorrer->prox;
			percorrer->prox = lista;
		}
		descritor->n++;
	}
	else {
		existe->cont++;
	}

	return NULL;
}


// Remove da lista
st_lista *remove_lista(descritor_lista *descritor)
{
	if(!descritor || !descritor->prim) return NULL;

	st_lista *percorrer = NULL;

	percorrer = descritor->prim;

	// remove do inicio
	descritor->prim = percorrer->prox;
	percorrer->prox = NULL;

	return percorrer;
}


/* Ordena a lista por InsertionSort
https://en.wikipedia.org/wiki/Insertion_sort */
st_lista *ordena_lista(descritor_lista *descritor) 
{
	st_lista *pList = descritor->prim;

    // zero or one element in list
    if(pList == NULL || pList->prox == NULL)
        return pList;

    // head is the first element of resulting sorted list
    st_lista * head = NULL;

    while(pList != NULL) 
    {
        st_lista * atual = pList;
        pList = pList->prox;

        if(head == NULL || atual->cont < head->cont) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            atual->prox = head;
            head = atual;
        } 
        else {
            // insert current element into proper position in non-empty sorted list
            st_lista *p = head;
            while(p != NULL) 
            {
                if(p->prox == NULL || // last element of the sorted list
                   atual->cont < p->prox->cont) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    atual->prox = p->prox;
                    p->prox = atual;
                    break; // done
                }
                p = p->prox;
            }
        }
    }
    descritor->prim = head;

    return head;
}


// Imprime lista
void imprime_lista(descritor_lista *descritor)
{
	if(!descritor || !descritor->prim) return;

	st_lista *percorrer = NULL;

	percorrer = descritor->prim;

	while(percorrer) {
		printf("%c ", percorrer->caracter);
		printf("%d\n", percorrer->cont);
		percorrer = percorrer->prox;
	}
}


// Insere ordenado na lista
void *insere_ordenado_lista(descritor_lista *descritor, st_lista *lista)
{
	st_lista *percorrer = NULL;

	if(!descritor) return NULL;

	// Lista vazia
	if(!descritor->prim || descritor->prim->cont >= lista->cont) {
		lista->prox = descritor->prim;
		descritor->prim = lista;
		return NULL;
	}

	percorrer = descritor->prim;

	while(percorrer->prox != NULL && 
		  percorrer->prox->cont < lista->cont) 
	{
		percorrer = percorrer->prox;
	}

	lista->prox = percorrer->prox;
	percorrer->prox = lista;

	return NULL;
}


// Gera arvore de Huffman
void *gera_arvore(descritor_lista *descritor)
{
	st_lista *esq = NULL, 
			 *dir = NULL,
			 *novo = NULL;

	if(!descritor || !descritor->prim) return NULL;

	while(descritor->prim->prox != NULL) {
		esq = remove_lista(descritor);
		dir = remove_lista(descritor);

		if(!esq || !dir) {
			printf("Erro gera_arvore\n");
			exit(EXIT_FAILURE);
		}

		novo = cria_lista('\0');
		novo->cont = esq->cont + dir->cont;
		novo->esq = esq;
		novo->dir = dir;

		insere_ordenado_lista(descritor, novo);
	}

	return NULL;
}


// Imprime arvore em ordem
void imprime_arvore(st_lista *raiz)
{
	st_lista *pRaiz = raiz;

    if(pRaiz != NULL) {
        imprime_arvore(pRaiz->esq);
        printf("%c - %d\n", pRaiz->caracter, pRaiz->cont);
        imprime_arvore(pRaiz->dir);
    }
}


// 
void imprime_vetor(int arr[], int n)
{
    int i = 0;

    for (i = 0; i < n; i++)
        printf("%d", arr[i]);
    printf("\n");
}


// Verifica se o no eh folha
int folha(st_lista *raiz)
{
    return !(raiz->esq) && !(raiz->dir) ;
}


void arrCpy(int src[], int dest[], int size)
{
	int i = 0;

	for(i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}


// Aloca vetor de inteiros
int *aloca_vetor(int n)
{
	return (int*) malloc(n * sizeof(int));
}


// Aloca vetor de codigos binarios
bin_code *aloca_bin(int n)
{
	return (bin_code*) malloc(n * sizeof(bin_code));
}


// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void imprime_codigos(st_lista *raiz, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if(raiz->esq) {
        arr[top] = 0;
        imprime_codigos(raiz->esq, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if(raiz->dir) {
        arr[top] = 1;
        imprime_codigos(raiz->dir, arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (folha(raiz)) {
        printf("%d: ", raiz->caracter);
        imprime_vetor(arr, top);
        codigos_bin[codigos_index].caracter = raiz->caracter;
        codigos_bin[codigos_index].code = aloca_vetor(top);
        codigos_bin[codigos_index].tam = top;
        arrCpy(arr, codigos_bin[codigos_index].code, top);
        codigos_index++;
    }
}


// Retorna indice do codigo correspondente ao caracter
int get_code_index(char caracter)
{
	int i = 0;

	for (i = 0; i < CODE_MAX_SIZE; i++)
	{
		if(codigos_bin[i].caracter == caracter)
			return i;
	}

	return - 1;
}


// Main
int main()
{
	int i, j;
	long lSize;
	char *buffer;
	size_t result;

	FILE *arquivo = NULL,
		 *arquivo_saida = NULL;
	descritor_lista *descritor = NULL;

	arquivo = fopen("microdados_enade_2014_CCSI.csv", "r");

	if(!arquivo) {
		fputs("File error", stderr); 
		exit(EXIT_FAILURE);
	}

	// obtem tamanho do arquivo
	fseek(arquivo , 0 , SEEK_END);
	lSize = ftell(arquivo);
	rewind(arquivo);

	// aloca memoria para todo o arquivo
	buffer = (char*) malloc(sizeof(char) * lSize);
	if(buffer == NULL) {
		fputs("Memory error", stderr); 
		exit(EXIT_FAILURE);
	}

	// copia o arquivo para o buffer
	result = fread(buffer, 1, lSize, arquivo);
	if(result != lSize) {
		fputs("Reading error", stderr); 
		exit (EXIT_FAILURE);
	}

	// fecha arquivo
	fclose (arquivo);

	descritor = cria_descritor_lista();

	for(int i = 0; i <= lSize; i++)
	{
		insere_lista(descritor, *(buffer + i));
	}  


	ordena_lista(descritor);
	imprime_lista(descritor);
	CODE_MAX_SIZE = descritor->n;
	codigos_bin = aloca_bin(CODE_MAX_SIZE);
	gera_arvore(descritor);

	int arr[CODE_MAX_SIZE];

	imprime_codigos(descritor->prim, arr, 0);


/*	for(i = 0; i < CODE_MAX_SIZE; ++i)
	{
		printf("!%d: ", codigos_bin[i].caracter);
		for(j = 0; j < codigos_bin[i].tam; j++)
		{
			printf("%d", codigos_bin[i].code[j]);
		}
		printf("\n");
	}
*/

	arquivo_saida = fopen("saida.bin", "w+b");

	unsigned int saida = 0, mascara, aux;
	unsigned int numBits;
	int cont, total = 0;

	for(i = 0; i <= lSize; i++)
	{
		int index = get_code_index(buffer[i]);
		for(j = 0; j < codigos_bin[index].tam; j++)
		{
			char entrada = codigos_bin[index].code[j];
			numBits = 1;

			//printf("entrada: %x saida: %x\n", entrada, saida);

			for(; numBits >= 1 && total < 32; total++) {
				saida = saida << 1;

				for(cont = 1, mascara = BIT_MAIS_BAIXO; cont < numBits; cont++)
					mascara = mascara << 1;
				aux = entrada & mascara;
				for(cont = 1; cont < numBits; cont++) 
					aux = aux >> 1;
				saida = saida | aux;
				//printf("entrada: %x saida: %x\n", entrada, saida);
				numBits--;
			}
			if(total == 32) {
				//done
				fwrite(&saida, sizeof(unsigned int), 1, arquivo_saida);
				if(ferror(arquivo_saida)) {
					perror(__func__);
					exit(EXIT_FAILURE);
				}
				saida = 0;
				total = 0;
			}


		}
	}
	if(total != 0) {
		int desl = 32 - total;
		total = total << desl;
		//done
		fwrite(&saida, sizeof(unsigned int), 1, arquivo_saida);
		if(ferror(arquivo_saida)) {
			perror(__func__);
			exit(EXIT_FAILURE);
		}
	}

	// hexdump -C saida.bin 
	// http://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree

	fclose(arquivo_saida);
	free (buffer);
	return EXIT_SUCCESS;
}