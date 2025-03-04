#include <stdio.h>

#define TAMANHO 10

typedef struct {
    int valores[TAMANHO];
    int n;
} Lista;

/**
 * @brief Verifica se a lista está cheia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver cheia, caso contrário, retorna 0.
 */
int esta_cheia(Lista *lista) {
    return lista -> n == TAMANHO;
}

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver vazia, caso contrário, retorna 0.
 */
int esta_vazia(Lista *lista) {
    return lista -> n == 0;
}

/**
 * @brief Encontra a posição onde um valor deve ser inserido na lista ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna o índice onde o valor deve ser inserido.
 */
int encontrar_posicao(Lista *lista, int valor) {
    int idx = 0;
    while(idx < lista -> n && valor > lista -> valores[idx]){
        idx++;
    }
    return idx;
}

/**
 * @brief Move os elementos da lista para a direita a partir de um índice, criando espaço para um novo valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_direita(Lista *lista, int indice) {
    for(int i = lista -> n; i >indice; i--){
        lista -> valores[i] = lista -> valores[i-1];
    }
}

/**
 * @brief Move os elementos da lista para a esquerda a partir de um índice, removendo um valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_esquerda(Lista *lista, int indice) {
    for(int i = indice; i < lista ->n; i++){
        lista -> valores[i] = lista -> valores[i+1];
    }
}

/**
 * @brief Insere um valor na lista em sua posição ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna 1 se a inserção for bem-sucedida, ou 0 se a lista estiver cheia.
 */
int inserir(Lista *lista, int valor) {
    if(esta_cheia(lista)){
        return 0;
    }
    int idx = encontrar_posicao(lista, valor);
    deslocar_direita(lista, idx);
    lista -> valores[idx] = valor;
    lista -> n++;
    return 1;
}


/**
 * @brief Remove um valor da lista.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser removido.
 * @return int Retorna o valor removido se a remoção for bem-sucedida, ou -1 se a lista estiver vazia.
 */
int remover(Lista *lista, int valor) {
    if(esta_vazia(lista)){
        return -1;
    }
    int indice = encontrar_posicao(lista, valor);
    int apagado = lista->valores[indice];
    deslocar_esquerda(lista, indice);
    lista -> n--;
    return apagado;
}

/**
 * @brief Exibe todos os valores da lista.
 * 
 * @param lista Ponteiro para a lista.
 */
void exibir_lista(const Lista *lista) {
    for(int i = 0; i < lista -> n; i++){
        printf("%d ", lista -> valores[i]);
    }
    printf("\n");
}

int main(void) {
    Lista lista = { .n = 0 };
    Lista *pl = &lista;
    int valores[] = {21, 14, 13, 10, 87, 35, 27, 56, 85, 29};

    for (int i = 0; i < TAMANHO; i++) {
        inserir(pl, valores[i]);
        exibir_lista(pl);
    }

    for (int i = 0; i < TAMANHO; i++) {
        printf("O valor %d está na posição %d\n", valores[i], encontrar_posicao(pl, valores[i]));
    }

    for (int i = 0; i < TAMANHO; i++) {
        remover(pl, valores[i]);
        exibir_lista(pl);
    }

    return 0;
}

