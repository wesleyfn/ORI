#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#define TRUE 1
#define FALSE 0

#ifndef STR_MAX
#define STR_MAX 50 //tamanho maximo da string
#endif // STR_MAX

#ifndef QTD_ARQUIVOS
#define QTD_ARQUIVOS 3 //define quantos arquivos serão lidos
#endif // QTD_ARQUIVOS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodeConsideradas {
    char palavra[STR_MAX]; //palavra lida
    int frequencia[QTD_ARQUIVOS]; //vetor de frequênci. frequência[i] = frequência que a palavra aparece no arquivo i+1.
    struct nodeConsideradas *esq, *dir;
} TNodeC;

typedef struct nodeDesconsideradas {
    char palavra[STR_MAX];
    struct nodeDesconsideradas *esq, *dir;
} TNodeD;

void gerarResposta(TNodeC **nodes, FILE *fConjunto, int n_arquivos, int n_palavras);

// Arvore das palavras consideradas
void delArvoreConsideradas(TNodeC *raiz);
void inOrderConsideradas(TNodeC *raiz);
TNodeC* criarNodeC(char palavra[STR_MAX], int arquivo);
TNodeC* inserirNodeC(TNodeC *raiz, char palavra[STR_MAX], int arquivo);
void escreverNodeC(TNodeC *raiz, char* arquivoNome);
void _escreve_(TNodeC *raiz, FILE *arquivo);

// Arvore das palavras desconsideradas
void delArvoreDesconsideradas(TNodeD *raiz);
TNodeD* inserirNodeD(TNodeD *raiz, char palavra[STR_MAX]);
TNodeD* criarNodeD(char palavra[STR_MAX]);
void inOrderDesconsideradas(TNodeD *raiz);
int taNaArvoreDesconsideradas(TNodeD *raiz, char palavra[STR_MAX]);

void gerarResposta(TNodeC **nodes, FILE *fConjunto, int n_arquivos, int n_palavras) 
{
    FILE *fRespostas = fopen("respostas.txt", "w+");
    int counter = 0;

    fprintf(fRespostas, "   \n");
    for (int i = 0; i < n_arquivos; i++)
    {
        int flag = TRUE;
        for (int j = 0; j < n_palavras; j++)
        {
            // Verifica se a frequencia a palavra é > 0
            // se for 0 encerra o loop, pois não é necessaria a verificação
            // das outras palavras já que a realação entre elas é AND.
            if (nodes[j]->frequencia[i] == 0) {
                flag = FALSE;
                break;
            }
        }
        
        // Imprime no arquivo resposta.txt se flag == 1, ou seja,
        // se a frequencia for != 0 em todos as palavras do arquivo
        if (flag == TRUE) {
            // i * strlen("a.txt")+1;
            fseek(fConjunto, i*6, SEEK_SET);

            char str[20];
            fscanf(fConjunto, "%s", str);
            fprintf(fRespostas, "%s\n", str);
            counter++;
        }
    }
    rewind(fRespostas);
    fprintf(fRespostas, "%d", counter);
    fclose(fRespostas);
}

void delArvoreConsideradas(TNodeC *raiz)
{
    if(raiz != NULL) {
        delArvoreConsideradas(raiz->esq);
        delArvoreConsideradas(raiz->dir);
        free(raiz);
    }
}
/*
void preOrderIndice(TNodeC *raiz)
{
    if(raiz != NULL)
    {
        printf("%s\n",raiz->palavra);
        preOrderIndice(raiz->esq);
        preOrderIndice(raiz->dir);
    }
}
*/
void inOrderConsideradas(TNodeC *raiz)
{
    if(raiz != NULL)
    {
        inOrderConsideradas(raiz->esq);

        printf("%s: ",raiz->palavra);
        for(int a = 0; a < QTD_ARQUIVOS; ++a) {
            if(raiz->frequencia[a] != 0)
                printf("%d,%d ",a+1,raiz->frequencia[a]);
        }
        printf("\n");

        inOrderConsideradas(raiz->dir);
    }
}

TNodeC* criarNodeC(char palavra[STR_MAX], int arquivo)
{
    TNodeC *buffer = (TNodeC*) malloc(sizeof(TNodeC));

    for(int a = 0; a < QTD_ARQUIVOS; ++a)
    {
        buffer->frequencia[a] = 0;
    }
    strncpy(buffer->palavra,palavra,STR_MAX);

    buffer->esq = NULL;
    buffer->dir = NULL;

    if(arquivo < QTD_ARQUIVOS)
        buffer->frequencia[arquivo] = 1;

    return buffer;
}

TNodeC* inserirNodeC(TNodeC *raiz, char palavra[STR_MAX], int arquivo)
{
    if(raiz == NULL)
        return criarNodeC(palavra,arquivo);

    int cmp = strcmp(raiz->palavra,palavra);

    if(cmp > 0)
    {
        raiz->esq = inserirNodeC(raiz->esq, palavra,arquivo);
    }
    else if(cmp < 0)
    {
        raiz->dir = inserirNodeC(raiz->dir, palavra,arquivo);
    }
    else
    {
        raiz->frequencia[arquivo] += 1;
    }

    return raiz;
}

void escreverNodeC(TNodeC *raiz, char* arquivoNome)
{
    FILE *arquivo = fopen(arquivoNome,"w");

    if(arquivo != NULL)
    {
        _escreve_(raiz,arquivo);
        fclose(arquivo);
    }
}

void _escreve_(TNodeC *raiz, FILE *arquivo)
{
    if(raiz != NULL)
    {
        _escreve_(raiz->esq, arquivo);

        fprintf(arquivo,"%s: ",raiz->palavra);

        for(int a = 0; a < QTD_ARQUIVOS; ++a)
        {
            if(raiz->frequencia[a] != 0)
                fprintf(arquivo,"%d,%d ",a+1,raiz->frequencia[a]);
        }
        fprintf(arquivo,"\n");

        _escreve_(raiz->dir,arquivo);
    }
}


void delArvoreDesconsideradas(TNodeD *raiz)
{
    if(raiz != NULL)
    {
        delArvoreDesconsideradas(raiz->esq);
        delArvoreDesconsideradas(raiz->dir);
        free(raiz);
    }
}

TNodeD* inserirNodeD(TNodeD *raiz, char palavra[STR_MAX])
{
    if(raiz == NULL)
        return criarNodeD(palavra);

    int cmp = strcmp(raiz->palavra, palavra);

    if(cmp > 0)
        raiz->esq = inserirNodeD(raiz->esq, palavra);
    else if(cmp < 0)
        raiz->dir = inserirNodeD(raiz->dir, palavra);

    return raiz;
}

TNodeD* criarNodeD(char palavra[STR_MAX])
{
    TNodeD *buffer = (TNodeD*) malloc(sizeof(TNodeD));

    strcpy(buffer->palavra, palavra);
    buffer->esq = NULL;
    buffer->dir = NULL;
    return buffer;
}

void inOrderDesconsideradas(TNodeD *raiz)
{
    if(raiz != NULL)
    {
        inOrderDesconsideradas(raiz->esq);
        printf("%s\n",raiz->palavra);
        inOrderDesconsideradas(raiz->dir);
    }
}

int taNaArvoreDesconsideradas(TNodeD *raiz, char palavra[STR_MAX])
{
    if(raiz != NULL)
    {
        int cmp = strcmp(raiz->palavra, palavra);

        //procura na direita
        if(cmp < 0)
            taNaArvoreDesconsideradas(raiz->dir, palavra);
        //procura na esquerda
        else if(cmp > 0)
            taNaArvoreDesconsideradas(raiz->esq, palavra);
        else
            return TRUE;
    }
}

TNodeC* selecionarConsultadas(TNodeC* arvore) {
    FILE *file = fopen("consulta.txt", "r");
    char str[STR_MAX];

    fscanf(file, "%s", str);


    fclose(file);
}

#endif // INDICE_H_INCLUDED