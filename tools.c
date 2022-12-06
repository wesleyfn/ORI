#include "tools.h"

// Funcao auxiliar, não está disponível para a main.c
void gerarIndice_(TNodeC *raiz, FILE *arquivo);

FILE* abrirArquivo(const char *diretorio, char *modo) {
    FILE *file = fopen(diretorio, modo);
    if (file == NULL) {
        printf("[ERRO!]\n> Arquivo \"%s\" nao encontrado!\n", diretorio);
        exit(-1);
    }
    else
        return file;
}

TNodeC* buscarPalavra(TNodeC *raiz, char *palavra)
{
    if(raiz != NULL)
    {
        int cmp = strcmp(raiz->palavra, palavra);

        //procura na direita
        if(cmp < 0)
            buscarPalavra(raiz->dir, palavra);
        //procura na esquerda
        else if(cmp > 0)
            buscarPalavra(raiz->esq, palavra);
        else
            return raiz;
    }
    else
        return NULL;
}

void gerarResposta(TNodeC **nodes, FILE *fConjunto, int n_palavras) 
{
    FILE *fRespostas = fopen("respostas.txt", "w+");
    int counter = 0;

    fprintf(fRespostas, "   \n");
    for (int i = 0; i < QTD_ARQUIVOS; i++)
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

            char str[STR_MAX];
            if(fscanf(fConjunto, "%s", str) != EOF)
                fprintf(fRespostas, "%s\n", str);
            counter++;
        }
    }
    rewind(fRespostas);
    fprintf(fRespostas, "%d", counter);
    fclose(fRespostas);
}

void delArvoreC(TNodeC *raiz)
{
    if(raiz != NULL) {
        delArvoreC(raiz->esq);
        delArvoreC(raiz->dir);
        free(raiz);
    }
}

void printArvoreC(TNodeC *raiz)
{
    if(raiz != NULL)
    {
        printArvoreC(raiz->esq);

        printf("%s: ",raiz->palavra);
        for(int a = 0; a < QTD_ARQUIVOS; ++a) {
            if(raiz->frequencia[a] != 0)
                printf("%d,%d ",a+1,raiz->frequencia[a]);
        }
        printf("\n");

        printArvoreC(raiz->dir);
    }
}

TNodeC* criarNodeC(char *palavra, int arquivo)
{
    TNodeC *buffer = (TNodeC*) calloc(1, sizeof(TNodeC));
    if (buffer == NULL){
        puts("Erro de alocacao!");
        exit(-1);
    }
    
    strncpy(buffer->palavra, palavra,STR_MAX);
    buffer->esq = NULL;
    buffer->dir = NULL;

    if(arquivo < QTD_ARQUIVOS)
        buffer->frequencia[arquivo] = 1;

    return buffer;
}

TNodeC* inserirNodeC(TNodeC *raiz, char *palavra, int arquivo)
{
    if(raiz == NULL)
        return criarNodeC(palavra, arquivo);

    int cmp = strcmp(raiz->palavra, palavra);

    if(cmp > 0)
        raiz->esq = inserirNodeC(raiz->esq, palavra,arquivo);
    else if(cmp < 0)
        raiz->dir = inserirNodeC(raiz->dir, palavra,arquivo);
    else if(cmp == 0)
        raiz->frequencia[arquivo] += 1;

    return raiz;
}

void gerarIndice(TNodeC *raiz)
{
    FILE *arquivo = fopen("indice.txt", "w+");
    if(arquivo != NULL) {
        gerarIndice_(raiz,arquivo);
        fclose(arquivo);
    }
}

void gerarIndice_(TNodeC *raiz, FILE *arquivo)
{
    if(raiz != NULL)
    {
        gerarIndice_(raiz->esq, arquivo);
        fprintf(arquivo, "%s: ",raiz->palavra);
        for(int i = 0; i < QTD_ARQUIVOS; i++)
        {
            if(raiz->frequencia[i] != 0)
                fprintf(arquivo,"%d,%d ", i+1, raiz->frequencia[i]);
        }
        fprintf(arquivo,"\n");
        gerarIndice_(raiz->dir,arquivo);
    }
}


void delArvoreD(TNodeD *raiz)
{
    if(raiz != NULL)
    {
        delArvoreD(raiz->esq);
        delArvoreD(raiz->dir);
        free(raiz);
    }
}

TNodeD* inserirNodeD(TNodeD *raiz, char *palavra)
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

TNodeD* criarNodeD(char *palavra)
{
    TNodeD *buffer = (TNodeD*) calloc(1, sizeof(TNodeD));
    if (buffer == NULL){
        puts("Erro de alocacao!");
        exit(-1);
    }
    strcpy(buffer->palavra, palavra);
    buffer->esq = NULL;
    buffer->dir = NULL;
    return buffer;
}

void printArvoreD(TNodeD *raiz)
{
    if(raiz != NULL)
    {
        printArvoreD(raiz->esq);
        printf("%s\n",raiz->palavra);
        printArvoreD(raiz->dir);
    }
}

int naArvoreD(TNodeD *raiz, char *palavra)
{
    if(raiz != NULL)
    {
        int cmp = strcmp(raiz->palavra, palavra);

        //procura na direita
        if(cmp < 0)
            naArvoreD(raiz->dir, palavra);
        //procura na esquerda
        else if(cmp > 0)
            naArvoreD(raiz->esq, palavra);
        else
            return TRUE;
    }
    else
        return FALSE;
}