#include <stdio.h>
#include <stdlib.h>

struct No{
    int chave;
    int peso;
    struct No* prox;
};

struct NoBusca{
    int distancia;
    struct NoBusca* pai;
};

struct Aresta{
    int no1;
    int no2;
    int peso;
};

typedef struct No No;
typedef struct NoBusca NoBusca;
typedef struct Aresta Aresta;

// Protótipos
No** lista_adjacencias(void);
void insere(No** vetor, int chave, int indice, int peso);
No* criaNo(int chave, int peso);
void imprime(No* vetor[], int tam);
void matriz_adjacencias(void);
void busca_amplitude(No* grafo[], int ponto_partida);
NoBusca* criaNoBusca(int distancia, NoBusca* pai);
void imprimeBusca(NoBusca* tabela[], int tam);
void kruskal(No* grafo[], int tam);
Aresta* criaAresta(int no1, int no2, int peso);
int procura_conflito(Aresta*** arvores, int qtd_arvores, Aresta* aresta);

int main(void){

    No** aux = lista_adjacencias();
    // matriz_adjacencias();
    // busca_amplitude(aux, 0);
    kruskal(aux, 10);

    return 0;
}

/*
Objetivo
- Fazer uma lista de adjacências

Descrição
- Criar um vetor com 10 posições
- O índice vai ser correspondente ao número do nó
- Em cada posição vai haver um ponteiro para uma estrutura
- Cada estrutura deverá ter o valor do nó adjacente e um ponteiro para o próximo nó

Assertivas de saída
- A função deve criar um grafo com os valores passados, imprimi-lo e devolve-lo

Assertivas de saída
- A função deve retornar um ponteiro para o vetor com o grafo montado
*/
No** lista_adjacencias(void){

    // Inicializa o vetor
    No** grafo = (No**)malloc(sizeof(No*)*10);
    if (grafo == NULL) exit(1);
    for(int i=0; i<10; i++){
        grafo[i] = NULL;
    }

    // Insere os valores desejados no grafo

    // Nó 0
    insere(grafo, 1, 0, 4);
    insere(grafo, 8, 0, 11);

    // Nó 1 
    insere(grafo, 0, 1, 4);
    insere(grafo, 3, 1, 8);
    insere(grafo, 8, 1, 11);

    // Nó 2

    // Nó 3 
    insere(grafo, 1, 3, 8);
    insere(grafo, 4, 3, 7);
    insere(grafo, 6, 3, 4);
    insere(grafo, 9, 3, 2);

    // Nó 4 
    insere(grafo, 3, 4, 7);
    insere(grafo, 5, 4, 9);
    insere(grafo, 6, 4, 14);

    // Nó 5
    insere(grafo, 4, 5, 9);
    insere(grafo, 6, 5, 10);

    // Nó 6
    insere(grafo, 3, 6, 4);
    insere(grafo, 4, 6, 14);
    insere(grafo, 5, 6, 10);
    insere(grafo, 7, 6, 2);

    // Nó 7
    insere(grafo, 6, 7, 2);
    insere(grafo, 8, 7, 1);
    insere(grafo, 9, 7, 6);

    // Nó 8
    insere(grafo, 0, 8, 8);
    insere(grafo, 1, 8, 11);
    insere(grafo, 7, 8, 1);
    insere(grafo, 9, 8, 7);

    // Nó 9
    insere(grafo, 3, 9, 2);
    insere(grafo, 7, 9, 6);
    insere(grafo, 8, 9, 7);

    // Imprime o grafo
    imprime(grafo, 10);

    return grafo;

}

/* 
Objetivo
- Colocar a chave no vetor pelo índice indicado

Descrição 
- Acessar o vetor no índice indicado
- Procurar um espaço NULL naquele nó
- Criar um struct No no lugar daquele NULL com a chave a ser inserida
- Fazer com que o ponteiro que apontava para NULL aponte para o novo nó

Parâmetros
- Vetor de ponteiros
- Chave a ser inserida
- Índice a inserir a chave no nó
- Peso da aresta

Assertivas de entrada
- Vetor deve ser um ponteiro para struct No
- Chave deve ser int
- Índice deve ser int
- Peso deve ser int

Assertivas de saída
- A função deve alterar o vetor no índice indicado, adicionando um nó com a chave passada e peso da aresta passada

*/
void insere(No* vetor[], int chave, int indice, int peso){

    if (vetor[indice] == NULL){
        vetor[indice] = criaNo(chave, peso);
        return;
    }

    // Cria um ponteiro para percorre a lista no vetor pelo índice indicado
    No* aux = vetor[indice];
    No* anterior;

    // Procura o primeiro espaço nulo, salvando o nó anterior
    for(; aux != NULL; aux = aux->prox){
        anterior = aux;
    }

    aux = criaNo(chave, peso);
    anterior->prox = aux;

    printf("** Chave %d inserida no índice %d **\n", chave, indice);
}

/*
Descrição
- Criar dinamicamente um nó
- Atribuir ao nó a chave passada como parâmetro
- Ponteiro para o próximo deve ser NULL

Parâmetros
- Chave a ser inserida
- Peso da aresta

Retorno
- Um ponteiro para o nó criado

Assertivas de entrada
- A chave deve ser int
- Peso deve ser int

Assertivas de saída
- A função deve retornar um ponteiro para o nó criado dinamicamente
*/
No* criaNo(int chave, int peso){
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) exit(1);
    novo_no->chave = chave;
    novo_no->peso = peso;
    novo_no->prox = NULL;
    return novo_no;
}

/*
Descrição
- Percorrer todo o vetor do grafo
- A cada índice, percorrer a lista encadeada imprimindo os valores até chegar em NULL

Parâmetros
- Ponteiro para vetor de ponteiros
- Tamanho do vetor

Assertivas de saída
- Índice do vetor deverá ser impresso
- Todos os valores armazenados devem ser impressos. Os índices que não possuem nada, não imprimirão nada.
*/
void imprime(No* vetor[], int tam){

    printf("\n<== LISTA DE ADJACÊNCIAS ==>\n");

    for(int i=0; i<tam; i++){

        printf("%d ", i);
        
        for(No* aux = vetor[i]; aux != NULL; aux = aux->prox){
            printf("--(%d)--> %d ", aux->chave, aux->peso);
        }

        printf("\n");

    }   

}

/*
Objetivo
- Criar uma matriz de adjacências

Descrição
- Criar um vetor estático com as dimensões indicadas
- Preenchê-lo com 0
- Acessar o índice desejado e preencher com 1 
- O índice deve ser acessado por [i][j] sendo i o nó trabalhado e j o nó adjacente

*/
void matriz_adjacencias(void){

    int grafo[10][10];

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            grafo[i][j] = 0;
        }
    }

    // Nó 0
    grafo[0][1] = 1;
    grafo[0][8] = 1;

    // Nó 1
    grafo[1][0] = 1;
    grafo[1][3] = 1;
    grafo[1][8] = 1;

    // Nó 2
    
    // Nó 3
    grafo[3][1] = 1;
    grafo[3][4] = 1;
    grafo[3][6] = 1;
    grafo[3][9] = 1;

    // Nó 4
    grafo[4][3] = 1;
    grafo[4][5] = 1;
    grafo[4][6] = 1;

    // Nó 5
    grafo[5][4] = 1;
    grafo[5][6] = 1;

    // Nó 6
    grafo[6][3] = 1;
    grafo[6][4] = 1;
    grafo[6][5] = 1;
    grafo[6][7] = 1;

    // Nó 7
    grafo[7][6] = 1;
    grafo[7][8] = 1;
    grafo[7][9] = 1;
    
    // Nó 8
    grafo[8][0] = 1;
    grafo[8][1] = 1;
    grafo[8][7] = 1;
    grafo[8][9] = 1;

    // Nó 9
    grafo[9][3] = 1;
    grafo[9][7] = 1;
    grafo[9][8] = 1;

    printf("\n<== MATRIZ DE ADJACÊNCIAS ==>\n");

    // Imprime o grafo
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }

}

/*
Objetivo
- Realizar uma busca em amplitude

Descrição
- Criar um vetor de ponteiros para estrutura NoBusca
- Cada índice do vetor corresponde ao número do nó
- Criar um vetor para armazenar os valores já vistados
- Criar um vetor para armazenar quais nós devem ser visitados
- Visitar os vizinhos do ponto de partida
- Armazenar a quantidadade de saltos
- Armazenar o "pai" desses vizinhos
- Adicionar esses vizinhos à pilha
- Adicionar esses vizinhos à lista de já visitados
- Repetir esse processo

Parâmetros
- Vetor com a lista de adjacências
- Ponto de partida
*/
void busca_amplitude(No* grafo[], int ponto_partida){

    // Tabela para armazenar a distância das chaves e seus pais
    NoBusca** tabela = (NoBusca**)malloc(sizeof(NoBusca*)*10);
    if (tabela == NULL) exit(1);
    for(int i=0; i<10; i++){
        tabela[i] = NULL;
    }

    // Vetor que armazena quais índices já foram visitados (1)
    int visitados[10];
    for(int i=0; i<10; i++){
        visitados[i] = 0; // (0): não visitado
    }

    // Vetor para armazenar quais os próximos nós a serem visitados (pilha)
    int pilha[10];
    for(int i=0; i<10; i++){
        pilha[i] = -1;
    }

    // Int que indica qual a primeira posição disponível na pilha
    int pilha_livre = 0;

    // Preenche os dados para o ponto de partida
    tabela[ponto_partida] = criaNoBusca(0, NULL);
    visitados[ponto_partida] = 1;
    pilha[pilha_livre++] = ponto_partida;

    // Int que armazena qual nó está sendo trabalhado no momento
    int atual;

    // Percorre a pilha
    for(int i=0; i<10 && pilha[i]!=-1; i++){

        atual = pilha[i];

        // Percorre os nós vizinhos do atual número da pilha
        for(No* aux = grafo[atual]; aux != NULL; aux = aux->prox){

            // Se este nó não tiver sido visitado
            if (!visitados[aux->chave]){

                // Adiciona na tabela
                tabela[aux->chave] = criaNoBusca(tabela[atual]->distancia+1, tabela[atual]);

                // Marca como visitado
                visitados[aux->chave] = 1;

                // Adiciona na pilha
                pilha[pilha_livre++] = aux->chave;
            }

        }
    }

    // Imprime a tabela
    imprimeBusca(tabela, 10);

}

/*
Descrição
- Criar dinamicamente um nó de busca
- Atribuir ao nó a distância passada como parâmetro
- Atribuir ao nó o pai passado como parâmetro

Parâmetros
- Distância
- Ponteiro para o pai

Retorno
- Um ponteiro para o nó criado

Assertivas de entrada
- Distância deve ser int
- Ponteiro para o pai deve ser struct NoBusca*

Assertivas de saída
- A função deve retornar um ponteiro para o nó criado dinamicamente
*/
NoBusca* criaNoBusca(int distancia, NoBusca* pai){
    NoBusca* novo_no = (NoBusca*)malloc(sizeof(NoBusca));
    if (novo_no == NULL) exit(1);
    novo_no->distancia = distancia;
    novo_no->pai = pai;
    return novo_no;
}

/*
Descrição
- Percorrer todos os NoBusca da tabela e exibir: índice, distância e endereço do pai

Parâmetros
- Vetor de ponteiros para NoBusca*
- Tamanho do vetor
*/
void imprimeBusca(NoBusca* tabela[], int tam){

    printf("\n");

    for(int i=0; i<tam; i++){
        printf("%d (%p) ->\t", i, tabela[i]);

        if (tabela[i]!=NULL){
            printf("Distância: %d\tPai: %p", tabela[i]->distancia, tabela[i]->pai);
        }

        printf("\n");

    }

}

/* 
Objetivo
- Criar o algoritmo de Kruskal para árvore geradora mínima

Descrição
- Procurar a aresta de menor peso
- Se essa aresta não conectar nós que já fazem parte da mesma árvore, fazer a ligação
- Fazer isso até que todos os nós estejam inclusos na árvore

Parâmetros
- Lista de adjacência do grafo
- Tamanho do grafo

Retorno

Assertivas de entrada

Assertivas de saída
*/
void kruskal(No* grafo[], int tam){

    // Estrutura para armazenar as árvore montadas
    Aresta*** arvores = (Aresta***)malloc(sizeof(Aresta**));
    if (arvores == NULL) exit(1);

    // Int para armazenar a quantidade de árvores existentes
    int tam_atual_arvores = 0;

    // Int para armazenar o tamanho da maior árvore montada
    int tam_maior_arvore = 0;

    // Estrutura para armazenar informações da aresta com menor peso
    Aresta* menor;

    // Enquanto a árvore não incluir todos os nós da árvore
    while(tam_maior_arvore < 10){

        // Percorre o grafo
        for(int i=0; i<tam; i++){

            // Se aquele nó tiver ligações
            if (grafo[i] != NULL){

                // Percorre as ligações do nó
                for(No* aux = grafo[i]; aux!=NULL; aux = aux->prox){
                    // Se o peso da aresta do nó trabalhado for menor que os demais E
                    if (aux->peso < menor->peso){
                        menor->no1 = i;
                        menor->no2 = aux->chave;
                        menor->peso = aux->peso;
                    }
                }

            }

        }

        // Se essa aresta não conectar dois pontos de uma mesma árvore
        if (!procura_conflito){

            // Se já existir uma árvore com um desses nós
                // Ligar os nós

            // Se não existir uma árvore com esses nós
                // Criar uma árvore e ligar os nós
                arvores[tam_atual_arvores] = (Aresta*)malloc(sizeof(Aresta)*9)
                if (arvores[tam_atual_arvores] == NULL) exit(1);

        }


    }

}

/*
Descrição
- Criar dinamicamente uma aresta com os valores passados

Parâmetros
- Nó 1
- Nó 2
- Peso da aresta

Retorno
- Ponteiro para a aresta

Assertivas de entrada
- Todos os parâmetros devem ser int

Assertivas de saída
- A aresta será criada dinamicamente na memória com os valores passados e um ponteiro à ela sera retornado
*/
Aresta* criaAresta(int no1, int no2, int peso){
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    if (nova_aresta == NULL) exit(1);
    nova_aresta->no1 = no1;
    nova_aresta->no2 = no2;
    nova_aresta->peso = peso;
    return nova_aresta;
}

/*
Objetivo
- Conferir se uma aresta conecta dois pontos de uma mesma árvore

Descrição
- Percorrer as árvores
- Se ambos nós da aresta estiverem na árvore, retornar 1
- Se não, continuar conferindo para as demais árvore
- Se não estiver em nenhuma árvore, retornar 0

Parâmetros
- Árvores
- Quantidade de árvores existentes
- Aresta

Retornos 
- 0
- 1
*/
int procura_conflito(Aresta*** arvores, int qtd_arvores, Aresta* aresta){

    // Variável auxiliar para percorrer a árvore
    Aresta* aux;

    // Flags para armazenar se o nó foi encontrado na árvore
    int flag1, flag2;

    // Percorre todas as árvores
    for(int i=0; i<qtd_arvores; i++){

        // Zera o flag para cada árvore
        flag1 = flag2 = 0;

        // Percorre uma árvore
        for(int j=0; j<9 && arvores[i][j]!= NULL; j++){

            // Muda o ponteiro de posição no vetor da árvore
            aux = arvores[i][j];

            // Se um dos nós for encontrado, atualiza sua respectiva flag
            if (aresta->no1 = aux->no1) flag1 = 1;
            else if (aresta->no2 = aux->no2) flag2 = 1;

        }

        // Se ambos os nós forem encontrados, encerrar o programa
        if (flag1 && flag2) return 1;

    }

    return 0;

}