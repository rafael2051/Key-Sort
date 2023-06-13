# Algoritmo de Key Sort em C

- Este repositório contém um arquivo chamado key_sort.c, um código escrito em c que abre um arquivo txt com vários registros e gera um novo arquivo txt com os registros ordenados pela chave. A chave é o primeiro campo de cada registro, que no contexto do meu exemplo é o número USP de cada aluno. No processo de ordenação através do key sort, o programa carrega na RAM uma tabela com os índices primários do arquivo txt original, ordena a tabela em ordem crescente baseado nas chaves, cria um árquivo binário "arq_bin1.bin" com os mesmos registros do arquivo txt original, e cria um novo arquivo binário ordenado "arq_bin1_ord.bin" que recebe os registros do "arq1_bin.bin" ordenados com auxílio da tabela de índices primários ordenada e da função key_sort(). Depois é criado um novo arquivo txt "arq1ord.txt", que recebe os registros de "arq1_bin.bin". Todos os arquivos são gerados na pasta "Saida".
- Para rodar o código, é necessário ter o gcc instalado no seu computador. Caso não tenha, clique nesse link para instalar mingw no windows: https://sourceforge.net/projects/mingw/. O instalador vem com o gcc e a biblioteca padrão do C.
- Para compilar, abra o terminal na mesma pasta de key_sort.c, e digite "gcc key_sort.c -o key_sort". Depois, para executar, digite "key_sort arq1.txt". Você também pode passar outros arquivo de texto como parâmetros para a função main, desde que siga as mesmas regras dos registros utilizados em arq1.txt.
