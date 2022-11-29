#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

int main(void)
{   
    TNodeD *desconsiderados = NULL;
    TNodeC *considerados = NULL;

    //abre o arquivo de palavras a serem desconsideradas.
    FILE *fDesconsiderados = fopen("desconsideradas.txt", "r"), *origem = NULL;

    //cria uma árvore com as palavras desconsideradas.
    char buffer[STR_MAX];
    fscanf(fDesconsiderados, "%s", buffer);
    

    desconsiderados = criarNodeD(buffer);

    while(fscanf(fDesconsiderados, "%s", buffer) != EOF)
    {
        inserirNodeD(desconsiderados, buffer);
    }

    //fecha o arquivo das desconsideradas.
    fclose(fDesconsiderados);

    origem = fopen("a.txt","r");
    fscanf(origem, "%s", buffer);

    considerados = criarNodeC(buffer, 0);

    
    while(fscanf(origem, "%s", buffer) != EOF)
    {
        int naArvore = FALSE;

        //se a palavra não for uma das excluidas, insere na árvore.
        naArvore = taNaArvoreDesconsideradas(desconsiderados, buffer);
        if(naArvore == FALSE)
            inserirNodeC(considerados,buffer,0);
    }

    fclose(origem);

    //escreve o resultado final
    escreverNodeC(considerados, "indice.txt");

    //exclui as duas árvores
    delArvoreDesconsideradas(desconsiderados);
    delArvoreConsideradas(considerados);

    FILE *file = fopen("consulta.txt", "r");
    char str[STR_MAX];

    fscanf(file, "%s", str);
    fclose(file);

    puts(str);

    /*
    TNode *casa = alocar(), *amor = alocar();
    
    FILE *fConjunto = fopen("conjunto.txt", "r+");

    strcpy(casa->palavra, "casa");
    casa->frequecia[0] = 1;
    casa->frequecia[1] = 0;
    casa->frequecia[2] = 1;

    strcpy(amor->palavra, "amor");
    amor->frequecia[0] = 1;
    amor->frequecia[1] = 1;
    amor->frequecia[2] = 1;


    int qtd_palavras = 2;
    int qtd_arquivos = 3;
    TNode *palavras[qtd_palavras];

    // A função de busca tem que retornar um ponteiro para a chave encontrada
    palavras[0] = casa;
    palavras[1] = amor;
    palavras[2] = casa;

    gerarResposta(palavras, fConjunto, qtd_arquivos, qtd_palavras);
    
    return 0;*/
}