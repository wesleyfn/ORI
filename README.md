# Sobre o projeto
Esse trabalho consiste na criação de um programa de gerenciamento de índices para um conjunto de arquivos no contexto de um sistema de Recuperação da Informação. Desenvolvido para avaliação na disciplina de Organização e Recuperação de Informação.

## Execução:
### Linux
- make
- ./main.exe conjunto.txt desconsideradas.txt consulta.txt

### Windows
- g++ main.c tools.c -o main.exe
- .\main.exe conjunto.txt desconsideradas.txt consulta.txt


## Arquivo indice.txt
O arquivo de saída indice.txt, conterá o índice gerado a partir dos documentos da base. Para a geração desse índice, é preciso considerar cada palavra não desconsiderada que apareça em algum dos documentos da base. Para cada uma dessas palavras no índice, é preciso apontar o número do arquivo em que a mesma aparece, e a quantidade de vezes em que a mesma aparece no arquivo. Os arquivos são numerados segundo a ordem em que aparecem no arquivo que indica os documentos do conjunto, que, para o nosso exemplo, foi denominado como conjunto.txt. Assim, o arquivo a.txt é o arquivo 1, o arquivo b.txt é o arquivo 2 e, por fim, o arquivo c.txt é o arquivo 3.

## Arquivo resposta.txt
O arquivo resposta.txt contém a resposta à consulta em consulta.txt. A primeira linha desse arquivo deve contêm a quantidade de documentos que satisfazem a consulta. As demais linhas contêm os arquivos da base que atendem a consulta.