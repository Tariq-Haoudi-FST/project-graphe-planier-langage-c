#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de graphe avec une matrice d'adjacence
struct Graph {
    int V; // Nombre de sommets
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

int contientSousMatricek5(int** matricePrincipale, int n, int c) {
    int k5[5][5] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };

    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j <= c - 5; j++) {
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
                return 1; // la graphe n'est pas planar
            }
        }
    }

    return 0; // la graphe est planar
}

int contientSousMatricek33(int** matricePrincipale, int n, int c) {
    int k33[6][6] = {
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 0}
    };

    for (int i = 0; i <= n - 6; i++) {
        for (int j = 0; j <= c - 6; j++) {
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
    int n, m;
    printf("Entrez le nombre de sommets : ");
    scanf("%d", &n);

    struct Graph* graph = createGraph(n);
    char s[10];

    // Saisie des arêtes du graphe
    printf("Entrez le nombre d'aretes du graphe : ");
    scanf("%d", &m);

    printf("Entrez les aretes du graphe (sous forme de paires de sommets) :\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        printf("Arete %d : ", i + 1);
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1); // Soustraire 1 car les sommets sont indexés à partir de 1
    }

    // Affichage de la matrice d'adjacence du graphe
    printf("Matrice d'adjacence du graphe :\n");
    displayGraph(graph);

    // Vérification de la présence de la sous-matrice K5 ou K33 dans la matrice principale (graphe)
    if (contientSousMatricek5(graph->adjMatrix, n, n) || contientSousMatricek33(graph->adjMatrix, n, n)) {
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