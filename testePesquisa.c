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
    escreverNodeC(considerados, "indice2.txt");

    //teste com as pesquisas:

    TNodeC *node[7];
    char *palavras[7] = {"casa","tinha","era","muito",
    "nada", "teto", "tinha"};

    buscarPalavra(considerados,node,7, palavras);

    for(int a = 0; a < 7; ++a)
    {
        if(node[a] != NULL)
            printf("%s\n",node[a]->palavra);
    }

    //exclui as duas árvores
    delArvoreDesconsideradas(desconsiderados);
    delArvoreConsideradas(considerados);
}