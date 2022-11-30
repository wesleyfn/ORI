#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strtok_r.h"
#include "tools.h"

void lerArquivosD(char arquivo_nome[], TNodeD ** raiz);
void lerArquivosC(char arquivo_nome[], TNodeC ** raiz, int arquivo);

int main(void)
{
    TNodeD *raiz = NULL;

    ler_arquivos_D("b.txt", &raiz);

    inOrderDesconsideradas(raiz);
    
    delArvoreDesconsideradas(raiz);
}
void lerArquivosD(char arquivo_nome[], TNodeD ** raiz){

    FILE *file;
    file = fopen(arquivo_nome, "r");
    char linha[STR_MAX], *rest = NULL;

    const char *s = "\n !,.?";

    rest = fgets(linha,STR_MAX,file);

    char * token = NULL;
    if(file == NULL){
        printf("Nao foi possivel ler o arquivo %s\n", arquivo_nome);
        exit(-1);
    }
    else{
         token = strtok_r(rest, s, &rest);
        *raiz = criarNodeD(token);
        do{
            while((token = strtok_r(rest, s, &rest))){
                inserirNodeD(*raiz, token);
            }
            rest = fgets(linha, STR_MAX, file);
        }while(rest != NULL);
    }
    fclose(file);
}

void lerArquivosC(char arquivo_nome[], TNodeC ** raiz, int arquivo){

    FILE *file;
    file = fopen(arquivo_nome, "r");
    char linha[STR_MAX], *rest = NULL;

    const char *s = "\n !,.?";

    rest = fgets(linha,STR_MAX,file);

    char * token = NULL;
    if(file == NULL){
        printf("Nao foi possivel ler o arquivo %s\n", arquivo_nome);
        exit(-1);
    }
    else{
         token = strtok_r(rest, s, &rest);
        *raiz = criarNodeC(token,arquivo);
        do{
            while((token = strtok_r(rest, s, &rest))){
                inserirNodeC(*raiz, token, arquivo);
            }
            rest = fgets(linha, STR_MAX, file);
        }while(rest != NULL);
    }
    fclose(file);
}