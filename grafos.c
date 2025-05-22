#include <stdio.h>
#include <stdbool.h>

#define V 6

int get_index(char x) {
    return x - 97;  // 'a' = 0, 'b' = 1, ...
}

void inicia_arestas(int arestas[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            arestas[i][j] = 0;
        }
    }
}

void cria_arestas(int arestas[V][V], int v, int u) {
    arestas[v][u] = 1;
}

void mostra_arestas(int arestas[V][V]) {
    printf("Matriz de Arestas:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
}

void mostra_adjacentes(int arestas[V][V], char v) {
    int index = get_index(v);
    printf("Adjacentes ao vértice %c: ", v);
    for (int j = 0; j < V; j++) {
        if (arestas[index][j] == 1) {
            printf("%c ", j + 97);
        }
    }
    printf("\n");
}

void mostra_distancias(int arestas[V][V], char v) {
    int index = get_index(v);
    int dist[V];
    bool visitado[V];

    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        visitado[i] = false;
    }

    dist[index] = 0;
    visitado[index] = true;

    int fila[V];
    int frente = 0, tras = 0;

    fila[tras++] = index;

    while (frente < tras) {
        int atual = fila[frente++];
        for (int i = 0; i < V; i++) {
            if (arestas[atual][i] == 1 && !visitado[i]) {
                fila[tras++] = i;
                visitado[i] = true;
                dist[i] = dist[atual] + 1;
            }
        }
    }

    printf("Distâncias a partir do vértice %c:\n", v);
    for (int i = 0; i < V; i++) {
        printf("Para %c: ", i + 97);
        if (dist[i] != -1)
            printf("%d\n", dist[i]);
        else
            printf("inacessível\n");
    }
}

int main() {
    int arestas[V][V];
    inicia_arestas(arestas);

    // Criando algumas arestas como exemplo
    cria_arestas(arestas, get_index('a'), get_index('b'));
    cria_arestas(arestas, get_index('a'), get_index('c'));
    cria_arestas(arestas, get_index('b'), get_index('d'));
    cria_arestas(arestas, get_index('c'), get_index('e'));
    cria_arestas(arestas, get_index('e'), get_index('f'));
    cria_arestas(arestas, get_index('d'), get_index('f'));

    mostra_arestas(arestas);

    printf("\n");
    mostra_adjacentes(arestas, 'a');

    printf("\n");
    mostra_distancias(arestas, 'a');

    return 0;
}