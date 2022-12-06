#include "tools.h"

// make
// ./main.exe conjunto.txt desconsideradas.txt consulta.txt
int main(int argc, const char **argv)
{
    if (argc == 4) 
    { 
        // Lendo os arquivos - nomes são passados como argumentos para main
        FILE *fConjunto = abrirArquivo(argv[1], "r");
        FILE *fDesconsideradas = abrirArquivo(argv[2], "r");
        FILE *fConsulta = abrirArquivo(argv[3], "r");           

        // Inicializando as raizes das arvores
        TNodeD *treeDesconsideradas = NULL;
        TNodeC *treeConsideradas = NULL;

        // Variaveis auxiliares
        char buffer[STR_MAX];
        int quantArq = 0, quantPalavras = 0;

        // Arvore desconsideradas
        while(fscanf(fDesconsideradas, "%s\n", buffer) != EOF)
            treeDesconsideradas = inserirNodeD(treeDesconsideradas, buffer);

        // Arvore consideradas
        while(fscanf(fConjunto, "%s", buffer) != EOF)
        {
            FILE *fileABC = fopen(buffer, "r");

            while (fscanf(fileABC, "%s", buffer) != EOF)
            {
                char *palavra = strtok(buffer, ".,!? ");
                
                // Se a palavra não for encontrada na arvore das desconsideradas
                if(!naArvoreD(treeDesconsideradas, palavra))
                    treeConsideradas = inserirNodeC(treeConsideradas, palavra, quantArq);
            }
            quantArq++;
            fclose(fileABC);
        }

        // Escrevendo a treeConsideradas no arquivo indice.txt
        gerarIndice(treeConsideradas);
        puts("> Arquivo \"indice.txt\" criado com sucesso!");

        // Verifica quantas palavras há no arquivo
        for ( ; fscanf(fConsulta, "%s", buffer) != EOF; quantPalavras++);
        
        // Volta para o inicio do arquivo
        rewind(fConsulta);

        // Guarda os nodes da arvore que possuem as palavras consultadas num vetor
        TNodeC *nodesConsultadas[quantPalavras];
        for (int i = 0; fscanf(fConsulta, "%s", buffer) != EOF; i++) {
            nodesConsultadas[i] = buscarPalavra(treeConsideradas, buffer);
        }

        // Gerando o arquivo resposta.txt
        gerarResposta(nodesConsultadas, fConjunto, quantPalavras);
        puts("> Arquivo \"respostas.txt\" criado com sucesso!");

        // Liberando memória e fechando arquivos
        fclose(fConjunto); 
        fclose(fConsulta); 
        fclose(fDesconsideradas);
        delArvoreC(treeConsideradas); 
        delArvoreD(treeDesconsideradas);
    }
    else {
        puts("[ERRO!]\n> Entre com o diretorio dos 3 arquivos .txt:");
        puts("> ex.: main.exe conjunto.txt desconsideradas.txt consulta.txt");
    }
    return 0;
}