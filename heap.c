#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int array[MAX];
    int tamanho;
} Heap;

void inicializarHeap(Heap *h) {
    h->tamanho = 0;
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void peneirar(Heap *h, int i) {
    int maior = i;
    int fe = 2 * i + 1;
    int fd = 2 * i + 2;

    if (fe < h->tamanho && h->array[fe] > h->array[maior])
        maior = fe;

    if (fd < h->tamanho && h->array[fd] > h->array[maior])
        maior = fd;

    if (maior != i) {
        trocar(&h->array[i], &h->array[maior]);
        peneirar(h, maior);
    }
}

void inserir(Heap *h, int valor) {
    if (h->tamanho == MAX) {
        printf("Heap cheia!\n");
        return;
    }

    int i = h->tamanho++;
    h->array[i] = valor;

    while (i > 0 && h->array[(i - 1) / 2] < h->array[i]) {
        trocar(&h->array[i], &h->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int remover(Heap *h) {
    if (h->tamanho <= 0) {
        printf("Heap vazia!\n");
        return -1;
    }

    int raiz = h->array[0];
    h->array[0] = h->array[--h->tamanho];
    peneirar(h, 0);

    return raiz;
}

void exibirHeap(Heap *h) {
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d ", h->array[i]);
    }
    printf("\n");
}

int main() {
    Heap h;
    inicializarHeap(&h);

    inserir(&h, 10);
    inserir(&h, 20);
    inserir(&h, 15);
    inserir(&h, 30);
    inserir(&h, 40);

    printf("Heap após inserção: ");
    exibirHeap(&h);

    printf("Elemento removido: %d\n", remover(&h));

    printf("Heap após remoção: ");
    exibirHeap(&h);

    return 0;
}
