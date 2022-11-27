#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#ifndef STR_MAX
#define STR_MAX 500 //tamanho maximo da string
#endif // STR_MAX

#ifndef QUANTOS_ARQUIVOS
#define QUANTOS_ARQUIVOS 30 //define quantos arquivos serão lidos
#endif // QUANTOS_ARQUIVOS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nodeIndice
{
    char palavra[STR_MAX]; //palavra lida
    int frequencia[QUANTOS_ARQUIVOS]; //vetor de frequênci. frequência[i] = frequência que a palavra aparece no arquivo i+1.

    struct nodeIndice *esquerdo, *direito;
};


typedef struct nodeIndice Indice;

Indice* criarIndice(char[STR_MAX], int);
void deletarArvoreIndice(Indice*); //deleta a arvore.
void inOrderIndice(Indice*); //print InOrder.
void preOrderIndice(Indice*); //print preOrder

void escreverIndice(Indice*,char*); //escreve um arquivo com os indices.
void _escreve_(Indice*,FILE*);

Indice *inserirIndice(Indice *, char[STR_MAX], int);

void deletarArvoreIndice(Indice *raiz)
{
    if(raiz != NULL)
    {
        deletarArvoreIndice(raiz->esquerdo);
        deletarArvoreIndice(raiz->direito);
        free(raiz);
    }
}

void preOrderIndice(Indice *raiz)
{
    if(raiz != NULL)
    {
        printf("%s\n",raiz->palavra);
        preOrderIndice(raiz->esquerdo);
        preOrderIndice(raiz->direito);
    }
}

void inOrderIndice(Indice *raiz)
{
    if(raiz != NULL)
    {
        inOrderIndice(raiz->esquerdo);

        printf("%s: ",raiz->palavra);
        for(int a = 0; a < QUANTOS_ARQUIVOS; ++a)
        {
            if(raiz->frequencia[a] != 0)
                printf("%d,%d ",a+1,raiz->frequencia[a]);
        }
        printf("\n");

        inOrderIndice(raiz->direito);
    }
}

Indice* criarIndice(char palavra[STR_MAX],int arquivo)
{
     Indice *buffer = (Indice*)malloc(sizeof(Indice));

    for(int a = 0; a < QUANTOS_ARQUIVOS; ++a)
    {
        buffer->frequencia[a] = 0;
    }
    strncpy(buffer->palavra,palavra,STR_MAX);

    buffer->esquerdo = NULL;
    buffer->direito = NULL;

    if(arquivo < QUANTOS_ARQUIVOS)
    buffer->frequencia[arquivo] = 1;

    return buffer;
}

Indice *inserirIndice(Indice *raiz, char palavra[STR_MAX], int arquivo)
{
    if(raiz == NULL)
        return criarIndice(palavra,arquivo);

    int cmp = strcmp(raiz->palavra,palavra);

    if(cmp > 0)
    {
        raiz->esquerdo = inserirIndice(raiz->esquerdo, palavra,arquivo);
    }
    else if(cmp < 0)
    {
        raiz->direito = inserirIndice(raiz->direito, palavra,arquivo);
    }
    else
    {
        raiz->frequencia[arquivo] += 1;
    }

    return raiz;
}

void escreverIndice(Indice *raiz, char* arquivoNome)
{
    FILE *arquivo = fopen(arquivoNome,"w");

    if(arquivo != NULL)
    {

        _escreve_(raiz,arquivo);
        fclose(arquivo);
    }
}

void _escreve_(Indice *raiz, FILE *arquivo)
{
    if(raiz != NULL)
    {
        _escreve_(raiz->esquerdo, arquivo);

        fprintf(arquivo,"%s: ",raiz->palavra);

        for(int a = 0; a < QUANTOS_ARQUIVOS; ++a)
        {
            if(raiz->frequencia[a] != 0)
                fprintf(arquivo,"%d,%d ",a+1,raiz->frequencia[a]);
        }
        fprintf(arquivo,"\n");

        _escreve_(raiz->direito,arquivo);
    }
}

#endif // INDICE_H_INCLUDED
