#include <stdio.h>
#include <stdlib.h>

#define TAM 10

// Estrutura do nó da lista encadeada
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Estrutura da tabela hash
typedef struct {
    No* tabela[TAM];
} hash;

// Função de hash: chave % TAM
int hash_func(int chave) {
    return chave % TAM;
}

// Inicializa todos os ponteiros da tabela como NULL
void inicializar(hash *h) {
    for (int i = 0; i < TAM; i++) {
        h->tabela[i] = NULL;
    }
}

// Insere valor na posição hash(chave)
void inserir(hash *h, int chave) {
    // Passo 1: Calcular a posição na tabela usando a função hash
    int pos = hash_func(chave);

    // Passo 2: Criar um novo nó
    No* novo = malloc(sizeof(No));
    novo->valor = chave;
    novo->prox = NULL;  // Inicialmente, o próximo nó é NULL

    // Passo 3: Verificar se já há algum valor na posição da tabela (colisão)
    if (h->tabela[pos] == NULL) {  
        // Se não houver colisão, o novo nó será o primeiro da lista
        h->tabela[pos] = novo;
    } else {
        // Caso haja colisão, insere o novo nó no início da lista
        novo->prox = h->tabela[pos];
        h->tabela[pos] = novo;
    }
}

// Remove valor da tabela
void remover(hash *h, int valor) {
    // Passo 1: Calcular a posição na tabela usando a função hash
    int pos = hash_func(valor);
    No *atual = h->tabela[pos];
    No *anterior = NULL;

    // Passo 2: Percorrer a lista encadeada para encontrar o nó com o valor
    while (atual != NULL) {
        if (atual->valor == valor) {
            // Caso 1: Se o valor for o primeiro da lista (no início)
            if (anterior == NULL) {
                h->tabela[pos] = atual->prox;  // Atualiza a tabela para o próximo nó
            } else {
                // Caso 2: Se o valor estiver no meio ou no final da lista
                anterior->prox = atual->prox;  // O anterior aponta para o próximo do atual
            }
            // Liberar a memória do nó removido
            free(atual);
            return;
        }
        // Avançar para o próximo nó
        anterior = atual;
        atual = atual->prox;
    }

    // Se o valor não foi encontrado
    printf("Valor %d não encontrado!\n", valor);
}

// Busca valor na tabela
int buscar(hash *h, int valor) {
    int pos = hash_func(valor);
    No *atual = h->tabela[pos];

    while (atual != NULL) {
        if (atual->valor == valor) {
            return 1; // encontrado
        }
        atual = atual->prox;
    }
    return 0; // não encontrado
}

// Função para mostrar a tabela
void mostrar(hash *h) {
    // Passo 1: Percorrer todas as posições da tabela hash
    for (int i = 0; i < TAM; i++) {
        printf("[%d] -> ", i);
        
        // Passo 2: Exibir os valores na lista encadeada na posição i
        No* atual = h->tabela[i];
        while (atual != NULL) {
            printf("%d -> ", atual->valor);  // Exibe o valor do nó
            atual = atual->prox;  // Avança para o próximo nó
        }
        printf("NULL\n");  // Marca o fim da lista
    }
}

int main() {
    hash *h = malloc(sizeof(hash));
    inicializar(h);

    int valor;

    // Inserir valores
    printf("=== Inserção ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Digite um valor para inserir: ");
        scanf("%d", &valor);
        inserir(h, valor);
    }
    mostrar(h);

    // Buscar valor
    printf("=== Buscar ===\n");
    printf("Digite um valor para buscar: ");
    scanf("%d", &valor);
    if (buscar(h, valor)) {
        printf("Valor %d está na hash!\n", valor);
    } else {
        printf("Valor %d NÃO está na hash.\n", valor);
    }

    // Remover valor
    printf("=== Remover ===\n");
    printf("Digite um valor para remover: ");
    scanf("%d", &valor);
    remover(h, valor);
    mostrar(h);

    return 0;
}