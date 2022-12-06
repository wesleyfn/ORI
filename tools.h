#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#ifndef STR_MAX
#define STR_MAX 20 // Tamanho maximo das strings
#endif 

#ifndef QTD_ARQUIVOS
#define QTD_ARQUIVOS 4 // Define quantos arquivos serão lidos
#endif

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodeConsideradas {
    char palavra[STR_MAX]; 
    int frequencia[QTD_ARQUIVOS]; // Vetor de frequencias. frequencia[i] = frequencia que a palavra aparece no arquivo i+1.
    struct nodeConsideradas *esq, *dir;
} TNodeC;

typedef struct nodeDesconsideradas {
    char palavra[STR_MAX];
    struct nodeDesconsideradas *esq, *dir;
} TNodeD;

// Gera o arquivo "resposta.txt"
void gerarResposta(TNodeC **nodes, FILE *fConjunto, int n_palavras);

// Gera o arquivo "indice.txt"
void gerarIndice(TNodeC *raiz);

// fopen com um tratamento de erro
FILE *abrirArquivo(const char *diretorio, char *modo);

/* ARVORE DAS PALAVRAS CONSIDERADAS */

// Libera a memoria utilizada pela arvore das consideradas
void delArvoreC(TNodeC *raiz);

// Imprime a arvore das consideradas em ordem alfabetica
void printArvoreC(TNodeC *raiz);

// Cria um novo node da arvore das consideradas
TNodeC* criarNodeC(char *palavra, int arquivo);

// Insire um novo node na arvore das consideradas
TNodeC* inserirNodeC(TNodeC *raiz, char *palavra, int arquivo);

// Busca e retorna um node que possui a determinada palavra na arvore das consideradas
TNodeC* buscarPalavra(TNodeC *raiz, char *palavra);


/* ARVORE DAS PALAVRAS DESCONSIDERADAS */

// Libera a memoria utilizada pela arvore das desconsideradas
void delArvoreD(TNodeD *raiz);

// Imprime a arvore das desconsideradas em ordem alfabetica
void printArvoreD(TNodeD *raiz);

// Cria um novo node da arvore das desconsideradas
TNodeD* criarNodeD(char *palavra);

// Insire um novo node na arvore das desconsideradas
TNodeD* inserirNodeD(TNodeD *raiz, char *palavra);

// Verifica se há determinada palavra na arvore das desconsideradas
int naArvoreD(TNodeD *raiz, char *palavra);

#endif 