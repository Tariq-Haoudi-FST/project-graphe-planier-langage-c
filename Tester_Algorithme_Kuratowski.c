#include <stdio.h>
#include <stdlib.h>

// Structure de graphe avec une matrice d'adjacence
struct Graph {
    int V;          // Nombre de sommets
    int** adjMatrix; // Matrice d'adjacence
};

// Fonction pour créer un graphe avec V sommets
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Allocation de la matrice d'adjacence
    graph->adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));
        // Initialisation de la matrice avec des zéros
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Fonction pour ajouter une arête au graphe non orienté
void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1; // Le graphe est non orienté
}

// Fonction pour afficher la matrice d'adjacence d'un graphe
void displayGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int contientSousMatricek5(int** matricePrincipale, int n, int m) {
    int k5[5][5] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };

    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j <= m - 5; j++) {
            int correspondance = 1;

            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 5; l++) {
                    if (matricePrincipale[i + k][j + l] != k5[k][l]) {
                        correspondance = 0;
                        break;
                    }
                }
                if (!correspondance) {
                    break;
                }
            }

            if (correspondance) {
                return 1; // le graphe n'est pas planar
            }
        }
    }

    return 0; // le graphe est planar
}

int contientSousMatricek33(int** matricePrincipale, int n, int m) {
    int k33[6][6] = {
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0}
    };

    for (int i = 0; i <= n - 6; i++) {
        for (int j = 0; j <= m - 6; j++) {
            int correspondance = 1;

            for (int k = 0; k < 6; k++) {
                for (int l = 0; l < 6; l++) {
                    if (matricePrincipale[i + k][j + l] != k33[k][l]) {
                        correspondance = 0;
                        break;
                    }
                }
                if (!correspondance) {
                    break;
                }
            }

            if (correspondance) {
                return 1; // le graphe n'est pas planar
            }
        }
    }

    return 0; // le graphe est planar
}

int main() {
    int n = 16, m = 16; // Vous devez initialiser n et m avec les valeurs correctes

    // Créer le graphe
    struct Graph* graph = createGraph(n);

    // Ajouter des arêtes (exemple)
    // Ajouter des arêtes (exemple)
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 8);
    addEdge(graph, 8, 9);
    addEdge(graph, 9, 10);
    addEdge(graph, 10, 11);
    addEdge(graph, 11, 12);
    addEdge(graph, 12, 13);
    addEdge(graph, 13, 14);
    addEdge(graph, 14, 1);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 6);
    addEdge(graph, 4, 7);
    addEdge(graph, 5, 8);
    addEdge(graph, 6, 9);
    addEdge(graph, 11, 15);
    addEdge(graph, 1, 6);
    addEdge(graph, 2, 7);
    addEdge(graph, 3, 8);
    addEdge(graph, 4, 9);
    addEdge(graph, 10, 14);
    addEdge(graph, 12, 15);
    addEdge(graph, 13, 14);
    addEdge(graph, 1, 7);
    addEdge(graph, 2, 8);
    addEdge(graph, 3, 9);
    addEdge(graph, 4, 5);
    addEdge(graph, 2, 3);
    addEdge(graph, 7, 8);
    addEdge(graph, 9, 10);
    addEdge(graph, 12, 13);
    addEdge(graph, 14, 1);
    addEdge(graph, 10, 11);
    addEdge(graph, 0, 15);
    addEdge(graph, 2, 12);
    // Ajoutez les autres arêtes ici...

    // Affichage de la matrice d'adjacence du graphe
    printf("Matrice d'adjacence du graphe :\n");
    displayGraph(graph);

    // Vérification de la présence de la sous-matrice K5 ou K33 dans la matrice principale (graphe)
    if (contientSousMatricek5(graph->adjMatrix, n, m) || contientSousMatricek33(graph->adjMatrix, n, m)) {
        printf("La matrice principale (graphe) est non planar.\n");
    } else {
        printf("La matrice principale (graphe) est planar.\n");
    }

    // Libération de la mémoire
    for (int i = 0; i < n; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
