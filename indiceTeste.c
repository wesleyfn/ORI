#include "gerenciarExcluidos.h"
#include "indice.h"

int main(void)
{
    Node *excluidos = NULL;
    Indice *palavras = NULL;

    //abre o arquivo de palavras a serem desconsideradas.
    FILE *exc = fopen("desconsiderados.txt","r"), *origem = NULL;


    //cria uma árvore com as palavras desconsideradas.
    char buffer[STR_MAX];
    fscanf(exc,"%s",buffer);

    excluidos = criarNo(buffer);

    while(fscanf(exc,"%s",buffer) != EOF)
    {
        inserir(excluidos,buffer);
    }

    //fecha o arquivo das desconsideradas.
    fclose(exc);

    origem = fopen("a.txt","r");
    fscanf(origem,"%s",buffer);

    palavras = criarIndice(buffer,0);


    int naArvore = 0;
    while(fscanf(origem,"%s",buffer) != EOF)
    {

        //se a palavra não for uma das excluidas, insere na árvore.
        taNaArvore(excluidos,buffer,&naArvore);
        if(!naArvore)
        inserirIndice(palavras,buffer,0);

        naArvore = 0;
    }

    fclose(origem);

    //escreve o resultado final
    escreverIndice(palavras,"saida.txt");

    //exclui as duas árvores
    deletarArvore(excluidos);
    deletarArvoreIndice(palavras);

    return 0;
}
