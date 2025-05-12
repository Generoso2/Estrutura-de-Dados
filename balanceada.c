#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int chave;
    int altura;
    struct Node* pai;
    struct Node* esq;
    struct Node* dir;
} Node;

int altura(Node* n) {
    return n ? n->altura : -1;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(Node* n) {
    return altura(n->dir) - altura(n->esq);
}

void atualizarAltura(Node* n) {
    if (n)
        n->altura = max(altura(n->esq), altura(n->dir)) + 1;
}

Node* rotacaoEsquerda(Node* x) {
    Node* y = x->dir;
    x->dir = y->esq;
    if (y->esq) y->esq->pai = x;

    y->esq = x;
    y->pai = x->pai;
    x->pai = y;

    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

Node* rotacaoDireita(Node* y) {
    Node* x = y->esq;
    y->esq = x->dir;
    if (x->dir) x->dir->pai = y;

    x->dir = y;
    x->pai = y->pai;
    y->pai = x;

    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

Node* balancear(Node* n) {
    atualizarAltura(n);
    int fb = fatorBalanceamento(n);

    // Direita pesada
    if (fb > 1) {
        if (fatorBalanceamento(n->dir) < 0)
            n->dir = rotacaoDireita(n->dir);
        return rotacaoEsquerda(n);
    }
    // Esquerda pesada
    else if (fb < -1) {
        if (fatorBalanceamento(n->esq) > 0)
            n->esq = rotacaoEsquerda(n->esq);
        return rotacaoDireita(n);
    }
    return n;
}

Node* inserir(Node* raiz, int chave, Node* pai) {
    if (!raiz) {
        Node* novo = malloc(sizeof(Node));
        novo->chave = chave;
        novo->altura = 0;
        novo->pai = pai;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave, raiz);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave, raiz);
    else
        return raiz; // duplicatas não são permitidas

    return balancear(raiz);
}

void imprimirInOrdem(Node* raiz) {
    if (raiz) {
        imprimirInOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimirInOrdem(raiz->dir);
    }
}

int main() {
    Node* raiz = NULL;

    int valores[] = {21, 26, 30, 9, 4, 14, 28, 18, 15, 10, 2, 3, 7};
    int n = sizeof(valores)/sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i], NULL);

    printf("Árvore em ordem:\n");
    imprimirInOrdem(raiz);
    printf("\n");

    return 0;
}